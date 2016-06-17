#include "sapphire.hpp"
#include <cstdlib>

#ifdef SAPPHIRE_OPENGL2
#include "opengl2/opengl2_context.hpp"
#endif

namespace Sapphire {

const struct PositionData zero_position = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};

Image::Image(unsigned a_w, unsigned a_h)
  : m_w(a_w)
  , m_h(a_h){
    
}

Image::~Image() { }

void Image::size(unsigned &a_w, unsigned &a_h) const {
    a_w = m_w;
    a_h = m_h;
}

unsigned Image::w() const{
    return m_w;
}

unsigned Image::h() const{
    return m_h;
}
    
Shape::Shape(Image *im)
  : m_image(im) {

}

Shape::~Shape(){

}

void Shape::image(Image *im){
    m_image = im;
}

Image *Shape::image(){
    return m_image;
}

const Image *Shape::image() const{
    return m_image;
}

bool ShaderProgram::attachShaders(Shader **shaders, unsigned num_shaders){
    for(unsigned i = 0; i < num_shaders; i++){
        if(!attachShader(shaders[i]))
            return false;
    }
    return true;
}

void ShaderProgram::setFrustum(float left, float right, float top, float bottom, float nearz, float farz){
    m_matrix.m_left = left;
    m_matrix.m_right = right;
    m_matrix.m_top = top;
    m_matrix.m_bottom = bottom;
    m_matrix.m_near = nearz;
    m_matrix.m_far = farz;
    
    m_matrix_mode = eFrustum;
}

void ShaderProgram::setOrtho(float left, float right, float top, float bottom, float nearz, float farz){
    m_matrix.m_left = left;
    m_matrix.m_right = right;
    m_matrix.m_top = top;
    m_matrix.m_bottom = bottom;
    m_matrix.m_near = nearz;
    m_matrix.m_far = farz;
    
    m_matrix_mode = eOrtho;
}
Group::Group()
  : m_position(NULL)
  , m_shapes((Shape**)malloc(64))
  , m_num_shapes(0)
  , m_shapes_capacity(8){

}
Group::~Group(){
    free(m_shapes);
}

void Group::addShapes(Shape **shapes, unsigned num_shapes){
    const unsigned starting_num_shapes = m_num_shapes;

    if(starting_num_shapes + num_shapes >= m_shapes_capacity){
        do{
            m_shapes_capacity <<= 1;
        }while(starting_num_shapes + num_shapes >= m_shapes_capacity);
        m_shapes = (Shape**)realloc(m_shapes, m_shapes_capacity);
    }
    
    for(unsigned i = 0; i < num_shapes; i++){
        m_shapes[starting_num_shapes + i] = shapes[i];
    }
    
    m_num_shapes += num_shapes;
}

void Group::addShape(Shape *shape){

    if(m_num_shapes + 1 >= m_shapes_capacity){
        m_shapes_capacity <<= 1;
        m_shapes = (Shape**)realloc(m_shapes, m_shapes_capacity);
    }
    
    m_shapes[m_num_shapes++] = shape;
}

struct PositionData *Group::position(){
    return m_position;
}

const struct PositionData *Group::position() const{
    return m_position;
}

void Group::position(struct PositionData *pos){
    m_position = pos;
}

ShaderProgram *Group::program(){
    return m_program;
}

ShaderProgram *Group::program() const{
    return m_program;
}

void Group::program(ShaderProgram *p){
    m_program = p;
}

void Group::draw(){
    if(m_program){
        if(m_position)
            m_program->bind(*m_position);
        else
            m_program->bind(zero_position);
    }
    for(unsigned i = 0; i < m_num_shapes; i++){
        m_shapes[i]->draw(*this);
    }
    if(m_program)
        m_program->unbind();
}

Context::~Context(){

}

Shader *Context::createShader(Shader::Type type) const{
    switch(type){
        case Shader::eFragment:
            return createFragmentShader();
        case Shader::eVertex:
            return createVertexShader();
        case Shader::eGeometry:
            return createGeometryShader();
    }
    return NULL;
}

void Context::setDefaultFrustum(float left, float right, float top, float bottom, float nearz, float farz){
    m_matrix.m_left = left;
    m_matrix.m_right = right;
    m_matrix.m_top = top;
    m_matrix.m_bottom = bottom;
    m_matrix.m_near = nearz;
    m_matrix.m_far = farz;
    
    m_matrix_mode = eFrustum;
}

void Context::setDefaultOrtho(float left, float right, float top, float bottom, float nearz, float farz){
    m_matrix.m_left = left;
    m_matrix.m_right = right;
    m_matrix.m_top = top;
    m_matrix.m_bottom = bottom;
    m_matrix.m_near = nearz;
    m_matrix.m_far = farz;
    
    m_matrix_mode = eOrtho;
}

void Context::applyDefaultMatrix(ShaderProgram &that) const{
    if(m_matrix_mode == eOrtho)
        that.setOrtho(m_matrix.m_left, m_matrix.m_right, 
            m_matrix.m_top, m_matrix.m_bottom,
            m_matrix.m_near, m_matrix.m_far);
    else
        that.setFrustum(m_matrix.m_left, m_matrix.m_right, 
            m_matrix.m_top, m_matrix.m_bottom,
            m_matrix.m_near, m_matrix.m_far);
}

Context *Context::Create(Type type){
    if(type){}
    #ifdef SAPPHIRE_OPENGL2
        if(type == eOpenGL2)
            return new OpenGL2_Context();
    #endif
    
    return NULL;
}
    
} // namespace Sapphire
