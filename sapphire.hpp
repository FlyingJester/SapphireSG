#pragma once
#include <cstdlib>

namespace Sapphire {

class Image {
public:
    Image(unsigned a_w, unsigned a_h);
    virtual ~Image();
    unsigned w() const;
    unsigned h() const;
    
    void size(unsigned &a_w, unsigned &a_h) const;
    
    virtual void lock(void *to) const = 0;
    virtual void unlock(const void *from) = 0;
protected:
    const unsigned m_w, m_h;
};

class Shader {
public:
    enum Type { eFragment, eVertex, eGeometry };

    Shader(Type);
    virtual ~Shader();

    virtual bool compile() = 0;
    virtual bool success() const = 0;
    virtual void getError(char *to, unsigned len) const = 0;

    Type type() const;
protected:
    const Type m_type;
};

struct PositionData {
    float m_x, m_y, m_z;
    float m_rot_x, m_rot_y, m_rot_z;
    float m_rot_angle_x, m_rot_angle_y, m_rot_angle_z;
};

extern const struct PositionData zero_position;

class ShaderProgram {
public:
    virtual ~ShaderProgram() {}

    virtual bool attachShaders(Shader **shaders, unsigned num_shaders = 1);
    virtual bool attachShader(Shader *shader) = 0;

    virtual bool link() = 0;
    virtual bool success() const = 0;
    virtual void getError(char *to, unsigned len) const = 0;
    
    virtual void setFrustum(float left, float right, float top, float bottom, float near, float far);
    virtual void setOrtho(float left, float right, float top, float bottom, float near, float far);
    
    virtual void bind(const struct PositionData &data) const = 0;
    virtual void unbind() const {}
    
    virtual void setDiffuseLight(float r, float g, float b) = 0;
    virtual void addPositionalLight(float r, float g, float b, float x, float y, float z) = 0;
    virtual void clearPositionalLights() = 0;
protected:

    struct {
        float m_left, m_right, m_top, m_bottom, m_near, m_far;
    } m_matrix;
    enum { eOrtho, eFrustum } m_matrix_mode;    
};

template<typename T>
struct Vertex {

    T m_data[5];

    inline T x() const { return m_data[0]; }
    inline T y() const { return m_data[1]; }
    inline T z() const { return m_data[2]; }
    inline T u() const { return m_data[3]; }
    inline T v() const { return m_data[4]; }

    inline void x(T i) { m_data[0] = i; }
    inline void y(T i) { m_data[1] = i; }
    inline void z(T i) { m_data[2] = i; }
    inline void u(T i) { m_data[3] = i; }
    inline void v(T i) { m_data[4] = i; }

    inline void xyz(T ax, T ay, T az){
        x(ax); y(ay); z(az);
    }

    Vertex() {
        m_data[0] = m_data[1] = m_data[2] = m_data[3] = m_data[4] = 0;
    }
    Vertex(T ax, T ay, T az) {
        x(ax); y(ay); z(az); u(0); v(0);
    }

    Vertex(T ax, T ay, T az, T au, T av){
        x(ax); y(ay); z(az); u(au); v(av);
    }
};

typedef Vertex<float> VertexF;

class Group;

class Shape {
public:

    Shape(Image *image = NULL);
    virtual ~Shape();

    virtual void image(Image *im);
    Image *image();
    const Image *image() const;

    virtual void draw(Group &that) const = 0;

protected:
    Image *m_image;
};

class Group {
public:
    Group();
    virtual ~Group();
    
    virtual void addShape(Shape *);
    virtual void addShapes(Shape **, unsigned num_shapes = 1);
    
    struct PositionData *position();
    const struct PositionData *position() const;
    void position(struct PositionData *pos = NULL);
    
    virtual ShaderProgram *program();
    virtual ShaderProgram *program() const;
    virtual void program(ShaderProgram *p);
    virtual void draw();
    
protected:

    struct PositionData *m_position;
    ShaderProgram *m_program;
    Shape **m_shapes;
    unsigned m_num_shapes, m_shapes_capacity;
};

class Context {
public:
    virtual ~Context();
    
    virtual void setDefaultFrustum(float left, float right, float top, float bottom, float near, float far);
    virtual void setDefaultOrtho(float left, float right, float top, float bottom, float near, float far);
    
    virtual const char *name() const = 0;
    virtual Image *createImage(const void *pixels, unsigned w, unsigned h) const = 0;
    
    virtual void getShaderLanguageVersion(unsigned &major, unsigned &minor) const = 0;

    virtual Shader *createFragmentShader() const = 0;
    virtual Shader *createVertexShader() const = 0;
    virtual Shader *createGeometryShader() const = 0;
    Shader *createShader(Shader::Type type) const;

    virtual ShaderProgram *createShaderProgram() = 0;
    
    // Vertices may be freed after creating a shape
    virtual Shape *createShape(VertexF *vertices, unsigned num_vertices) const = 0;
    // Shapes must not be freed if the Group will be drawn again.
    virtual Group *createGroup(Shape **shapes, unsigned num_shapes = 1) const = 0;
    
    void applyDefaultMatrix(ShaderProgram &that) const;
    
    virtual void clearScreen() const = 0;
    
    enum Type {
        eOpenGL2,
        eOpenGL4,
        eSoftware,
        eVulkan
    };
    
    static Context *Create(Type type);
    
protected:
    struct {
        float m_left, m_right, m_top, m_bottom, m_near, m_far;
    } m_matrix;
    enum {eOrtho, eFrustum } m_matrix_mode;
};

} // namespace Sapphire
