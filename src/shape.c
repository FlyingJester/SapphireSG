#include "shape.h"
#include "backend.h"
#include <assert.h>


SAPPHIRESG_API_EXPORT
bool SG_SetShapeVertexCapacity(struct SapphireSG_Context *ctx, struct SapphireSG_Shape *shape, unsigned n) {
    assert(ctx);
    assert(shape);

    shape->num_vertices = n;
    if (shape->vertices_capacity < n){
        do {
            shape->vertices_capacity<<=1;
        } while (shape->vertices_capacity < n);
        shape->vertices = realloc(shape->vertices, sizeof(struct SapphireSG_Vertex) * shape->vertices_capacity);
    }

    return true;
}

SAPPHIRESG_API_EXPORT
unsigned SG_GetShapeVertexCapacity(struct SapphireSG_Context *ctx, const struct SapphireSG_Shape *shape) {
    assert(ctx);
    assert(shape);

    return shape->num_vertices;
}

SAPPHIRESG_API_EXPORT
bool SG_SetShapeImage(struct SapphireSG_Context *ctx, struct SapphireSG_Shape *shape, struct SapphireSG_Image *im) {
    assert(ctx);
    assert(shape);
    assert(im);
    
    shape->image = im;
    return true;
}

SAPPHIRESG_API_EXPORT
const struct SapphireSG_Image *SG_GetShapeImage(struct SapphireSG_Context *ctx, const struct SapphireSG_Shape *shape) {
    assert(ctx);
    assert(shape);

    return shape->image;
}

SAPPHIRESG_API_EXPORT
bool SG_SetShapeVertexPosition(struct SapphireSG_Context *ctx, struct SapphireSG_Shape *shape, unsigned i, float x, float y, float z) {
    assert(ctx);
    assert(shape);
    assert(i < shape->num_vertices);

    SG_XYZ(shape->vertices[i], x, y, z);

	shape->dirty = true;

    return true;
}

SAPPHIRESG_API_EXPORT
bool SG_GetShapeVertexPosition(struct SapphireSG_Context *ctx, const struct SapphireSG_Shape *shape, unsigned i, float *x, float *y, float *z) {
    assert(ctx);
    assert(shape);
    assert(i < shape->num_vertices);

    if (x)
        x[0] = SG_X(shape->vertices[i]);
    if (y)
        y[0] = SG_Y(shape->vertices[i]);
    if (z)
        z[0] = SG_Z(shape->vertices[i]);

    return true;
}

SAPPHIRESG_API_EXPORT
bool SG_GetShapeVertexTexturePosition(struct SapphireSG_Context *ctx, const struct SapphireSG_Shape *shape, unsigned i, float *u, float *v) {
    assert(ctx);
    assert(shape);
    assert(i < shape->num_vertices);

    if (u)
        u[0] = SG_U(shape->vertices[i]);
    if (v)
        v[0] = SG_V(shape->vertices[i]);

    return true;

}

SAPPHIRESG_API_EXPORT
bool SG_SetShapeVertexTexturePosition(struct SapphireSG_Context *ctx, struct SapphireSG_Shape *shape, unsigned i, float u, float v) {
    assert(ctx);
    assert(shape);
    assert(i < shape->num_vertices);

    SG_UV(shape->vertices[i], u, v);

	shape->dirty = true;

    return true;
}
