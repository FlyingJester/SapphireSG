#pragma once
#include "../sapphire.hpp"
#include "../openglextra/opengl.h"
#include <algorithm>
#include <utility>

namespace Sapphire {

class OpenGL2_Image : public Image {
    const GLuint name;
public:
    OpenGL2_Image(GLuint n, unsigned a_w, unsigned a_h);
    virtual ~OpenGL2_Image();

    virtual void lock(void *to) const;
    virtual void unlock(const void *from);
};

class OpenGL2_ShaderProgram : public ShaderProgram{
public:
    void applyMatrix() const;
    
    virtual bool link() { return true; }
    virtual bool success() const { return true; }
    virtual void getError(char *z, unsigned l) const { if (z || l) {} }
    
    virtual bool attachShader(Shader *z) { return !z; }
    
    virtual void bind(const struct PositionData &data) const;
    virtual void unbind() const;
    
    void getDiffuseLight(unsigned char &r, unsigned char &g, unsigned char &b) const;
    inline void getNearLights(float *xyz, unsigned char &r, unsigned char &g, unsigned char &b) const{
        getNearLights(xyz[0], xyz[1], xyz[2], r, g, b);
    }
    void getNearLights(float x, float y, float z, unsigned char &r, unsigned char &g, unsigned char &b) const;
    
    virtual void setDiffuseLight(float r, float g, float b);
    virtual void addPositionalLight(float r, float g, float b, float x, float y, float z);
    virtual void clearPositionalLights();
protected:
    struct GL2_Light {
        unsigned char m_color[3];
        float m_pos[3];
    } m_diffuse;
    
    GL2_Light *m_lights;
    unsigned m_num_lights, m_lights_capacity;
    
};
class OpenGL2_Shape : public Shape {
    VertexF *const m_vertices;
    const unsigned m_num_vertices;
public:
    OpenGL2_Shape(VertexF *v, unsigned n);
    virtual ~OpenGL2_Shape();
    virtual void draw(Group &that) const;
};



class OpenGL2_Group : public Group {
public:
    const OpenGL2_ShaderProgram *getShaderProgram() const;
};

class OpenGL2_Context : public Context {
public:
    OpenGL2_Context();

    virtual const char *name() const { return "OpenGL2"; }
    virtual Image *createImage(const void *pixels, unsigned w, unsigned h) const;
    
    virtual void getShaderLanguageVersion(unsigned &major, unsigned &minor) const { major = 0; minor = 0; }

    virtual Shader *createFragmentShader() const { return NULL; }
    virtual Shader *createVertexShader() const { return NULL; }
    virtual Shader *createGeometryShader() const { return NULL; }

    virtual ShaderProgram *createShaderProgram();
    
    virtual Shape *createShape(VertexF *vertices, unsigned num_vertices) const;
    virtual Group *createGroup(Shape **shapes, unsigned num_shapes = 1) const;

    virtual void clearScreen() const;
};

} // namespace Sapphire 
