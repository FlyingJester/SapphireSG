#include "opengl4_shape.h"
#include "../SapphireGLExtra/opengl.h"
#include "../SapphireGLExtra/opengl_shape.h"

#define PREDEFINED_GL_MODES 5

static const unsigned gl_draw_mode[PREDEFINED_GL_MODES] = {
	GL_TRIANGLE_STRIP,
	GL_POINTS,
	GL_LINE_LOOP,
	GL_TRIANGLE_STRIP,
	GL_TRIANGLE_FAN
};

struct SapphireSG_ShapeGuts *OpenGL4SG_CreateShape(struct SapphireSG_Context *ctx) {
	struct SapphireSG_ShapeGuts *guts = malloc(sizeof(struct SapphireSG_ShapeGuts));

	glGenBuffers(3, guts->buffer);
	glGenVertexArrays(1, &guts->vao);

	return guts;

}

void OpenGL4SG_DestroyShape(struct SapphireSG_Context *ctx, struct SapphireSG_Shape *shape) {
	assert(ctx);
	assert(shape);

	glDeleteBuffers(3, shape->guts->buffer);
	glDeleteVertexArrays(1, &shape->guts->vao);

	free(shape->guts);
}

void OpenGL4SG_DrawShape(struct SapphireSG_Context *ctx, struct SapphireSG_Shape *shape) {
	const GLenum mode = (shape->num_vertices < PREDEFINED_GL_MODES) ?
		gl_draw_mode[shape->num_vertices] : GL_TRIANGLE_STRIP;
	glDrawArrays(mode, 0, shape->num_vertices);
}

void OpenGL4SG_UpdateShape(struct SapphireSG_Context *ctx, struct SapphireSG_Shape *shape) {

	SapphireOpenGLExtra_UploadVertices(
		shape->guts->buffer[0], shape->guts->buffer[1], shape->guts->buffer[2],
		shape->vertices, shape->num_vertices);

}
