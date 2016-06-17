#include "opengl2_context.hpp"
#include "../openglextra/opengl_image.h"
#include <algorithm>
#include <utility>
#include <cmath>
#include <cassert>

namespace Sapphire {

OpenGL2_Image::OpenGL2_Image(GLuint n, unsigned a_w, unsigned a_h)
  : Image(a_w, a_h)
  , name(n){
    assert(n);
}

OpenGL2_Image::~OpenGL2_Image(){
    OpenGLExtra_DestroyImage(name);
}

void OpenGL2_Image::lock(void *to) const{
    assert(to);
    OpenGLExtra_ReadImage(name, reinterpret_cast<unsigned char *>(to), m_w, m_h);
}

void OpenGL2_Image::unlock(const void *from){
    assert(from);
    OpenGLExtra_UploadImage(name, reinterpret_cast<const unsigned char *>(from), m_w, m_h);
}

OpenGL2_Shape::OpenGL2_Shape(VertexF *v, unsigned n)
  : m_vertices((VertexF *)malloc(n * sizeof(VertexF)))
  , m_num_vertices(n){
    memcpy(m_vertices, v, m_num_vertices * sizeof(VertexF));
}

OpenGL2_Shape::~OpenGL2_Shape(){
    free(m_vertices);
}

void OpenGL2_Shape::draw(Group &that) const {
    OpenGL2_Group &group = *static_cast<OpenGL2_Group*>(&that);

    if(m_num_vertices == 0)
        return;
    if(m_num_vertices == 1)
        glBegin(GL_POINTS);
    if(m_num_vertices == 2)
        glBegin(GL_LINE_STRIP);
    if(m_num_vertices == 4)
        glBegin(GL_TRIANGLE_FAN);
    else
        glBegin(GL_TRIANGLE_STRIP);

    unsigned char dr = 0xFF, dg = 0xFF, db = 0xFF;
    const OpenGL2_ShaderProgram *const program = group.getShaderProgram();
    if(program){
        program->getDiffuseLight(dr, dg, db);
    }
    else
        glColor4ub(0xFF, 0xFF, 0xFF, 0xFF);

    for(unsigned i = 0; i < m_num_vertices; i++){
        
        /*
        TODO: Normals
        Begin Function CalculateSurfaceNormal (Input Polygon) Returns Vector

           Set Vertex Normal to (0, 0, 0)

           Begin Cycle for Index in [0, Polygon.vertexNumber)

              Set Vertex Current to Polygon.verts[Index]
              Set Vertex Next    to Polygon.verts[(Index plus 1) mod Polygon.vertexNumber]

              Set Normal.x to Sum of Normal.x and (multiply (Current.y minus Next.y) by (Current.z plus Next.z))
              Set Normal.y to Sum of Normal.y and (multiply (Current.z minus Next.z) by (Current.x plus Next.x))
              Set Normal.z to Sum of Normal.z and (multiply (Current.x minus Next.x) by (Current.y plus Next.y))

           End Cycle

           Returning Normalize(Normal)

        End Function
        */
        if(program){
            unsigned char lr = 0xFF, lg = 0xFF, lb = 0xFF;
            program->getNearLights(m_vertices[i].m_data, lr, lg, lb);
            const unsigned r = dr + lr,
                g = dg + lg,
                b = db + lb;
            
            glColor3ub(r, g, b);
        }
        
        glTexCoord2fv(m_vertices[i].m_data + 3);
		glVertex3fv(m_vertices[i].m_data);
    }
	glEnd();
};

void OpenGL2_ShaderProgram::applyMatrix() const{
    if(m_matrix_mode == eOrtho){
        glMatrixMode(GL_MODELVIEW);
    	glOrtho(m_matrix.m_left, m_matrix.m_right, 
            m_matrix.m_top, m_matrix.m_bottom,
            m_matrix.m_near, m_matrix.m_far);
        glDisable(GL_DEPTH_TEST);
        glDisable(GL_LIGHTING);
    }
    else{
        glMatrixMode(GL_PROJECTION);
    	glFrustum(m_matrix.m_left, m_matrix.m_right, 
            m_matrix.m_top, m_matrix.m_bottom,
            m_matrix.m_near, m_matrix.m_far);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_LIGHTING);
    }
}

void OpenGL2_ShaderProgram::bind(const struct PositionData &data) const{
    glPushMatrix();
    glTranslatef(data.m_x, data.m_y, data.m_z);
//    assert(false && "Implement this!");
}

void OpenGL2_ShaderProgram::unbind() const{

    glPopMatrix();
//    assert(false && "Implement this!");
}

template<typename T>
static T gl2_distance_squared(T a, T b, T c, T x, T y, T z){
    const T q = a - x, r = b - y, s = c - z;
    return (q * q) + (r * r) + (s * s);
}

template<typename T>
static T gl2_distance_squared(T *t, T x, T y, T z){
    return gl2_distance_squared(t[0], t[1], t[2], x, y, z);
}

void OpenGL2_ShaderProgram::getDiffuseLight(unsigned char &r, unsigned char &g, unsigned char &b) const {
    r = m_diffuse.m_color[0];
    g = m_diffuse.m_color[1];
    b = m_diffuse.m_color[2];
}

void OpenGL2_ShaderProgram::getNearLights(
    float x, float y, float z, unsigned char &r, unsigned char &g, unsigned char &b) const {

    r = g = b = 0;

    if(m_num_lights == 0)
        return;

    struct l_result { 
        unsigned m_index;
        float m_distance_squared;
        
        inline void swap(l_result &other){
            std::swap(m_index, other.m_index);
            std::swap(m_distance_squared, other.m_distance_squared);
        }
    } results[3] = { {0u, 0xFFFF}, {0u, 0xFFFF}, {0u, 0xFFFF } };
    // 0xFFFF is sufficiently large that lights farther than this will certainly have zero effect.
    

    // Sort through to find the three nearest lights
    for(unsigned i = 0; i < m_num_lights; i++){
        const float distance_squared = gl2_distance_squared(m_lights[i].m_pos, x, y, z);
        if(distance_squared < results[2].m_distance_squared){
            results[2].m_distance_squared = distance_squared;
            results[2].m_index = i;
            if(distance_squared < results[1].m_distance_squared){
                results[2].swap(results[1]);
                if(distance_squared < results[0].m_distance_squared)
                    results[1].swap(results[0]);
            }
        }
        
        assert(results[2].m_distance_squared >= results[1].m_distance_squared);
        assert(results[1].m_distance_squared >= results[0].m_distance_squared);
        
    }
    
    // Apply the lights as equally weighted inverse square brightnesses.
    // The actual method allows for higher than 1.0 levels of resolution.
    for(unsigned i = 0; i < 3; i++){
        const float m_r = r + ((0.5f / results[i].m_distance_squared) * static_cast<float>(m_lights[results[i].m_index].m_color[0])),
            m_g = g + ((0.5f / results[i].m_distance_squared) * static_cast<float>(m_lights[results[i].m_index].m_color[1])),
            m_b = b + ((0.5f / results[i].m_distance_squared) * static_cast<float>(m_lights[results[i].m_index].m_color[2]));
        
        r = std::max<unsigned short>(0xFF, m_r);
        g = std::max<unsigned short>(0xFF, m_g);
        b = std::max<unsigned short>(0xFF, m_b);
    }
}

void OpenGL2_ShaderProgram::setDiffuseLight(float r, float g, float b){
    m_diffuse.m_color[0] = r * 255.0f;
    m_diffuse.m_color[1] = g * 255.0f;
    m_diffuse.m_color[2] = b * 255.0f;
}

void OpenGL2_ShaderProgram::addPositionalLight(float r, float g, float b, float x, float y, float z){
    const unsigned n = m_num_lights++;
    if(m_num_lights >= m_lights_capacity){
        m_lights_capacity <<= 1;
        m_lights = (GL2_Light*)realloc(m_lights, m_lights_capacity);
    }
    
    m_lights[n].m_color[0] = r * 255.0f;
    m_lights[n].m_color[1] = g * 255.0f;
    m_lights[n].m_color[2] = b * 255.0f;
    
    m_lights[n].m_pos[0] = x;
    m_lights[n].m_pos[1] = y;
    m_lights[n].m_pos[2] = z;
}

void OpenGL2_ShaderProgram::clearPositionalLights(){
    m_num_lights = 0;
}

const OpenGL2_ShaderProgram *OpenGL2_Group::getShaderProgram() const{
    return static_cast<const OpenGL2_ShaderProgram*>(m_program);
}

OpenGL2_Context::OpenGL2_Context(){
    OpenGLExtra_LoadGLFunctions(NULL);
}

ShaderProgram *OpenGL2_Context::createShaderProgram(){
    return new OpenGL2_ShaderProgram();
}

Image *OpenGL2_Context::createImage(const void *pixels, unsigned w, unsigned h) const{
    return new OpenGL2_Image(OpenGLExtra_CreateImage((const unsigned char *)pixels, w, h), w, h);
}

Shape *OpenGL2_Context::createShape(VertexF *vertices, unsigned num_vertices) const {
    return new OpenGL2_Shape(vertices, num_vertices);
}

Group *OpenGL2_Context::createGroup(Shape **shapes, unsigned num_shapes) const {
    Group *const g = new OpenGL2_Group();
    g->addShapes(shapes, num_shapes);
    return g;
}

void OpenGL2_Context::clearScreen() const {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

} // namespace Sapphire
