#include "opengl4_shape.h"
#include "../SapphireGLExtra/opengl.h"
#include "../SapphireGLExtra/opengl_shape.h"

struct SapphireSG_ShapeGuts *OpenGL4SG_CreateShape(struct SapphireSG_Context *ctx) {
	struct SapphireSG_ShapeGuts *guts = malloc(sizeof(struct SapphireSG_ShapeGuts));

	glGenBuffers(3, guts->buffer);
	glGenVertexArrays(1, &guts->vao);

	return guts;

}

void OpenGL4SG_UpdateShape(struct SapphireSG_Context *ctx, struct SapphireSG_Shape *shape) {

	SapphireOpenGLExtra_UploadVertices(
		shape->guts->buffer[0], shape->guts->buffer[1], shape->guts->buffer[2],
		shape->vertices, shape->num_vertices);

}
