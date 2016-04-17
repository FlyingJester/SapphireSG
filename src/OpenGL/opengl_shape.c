#include "opengl_shape.h"
#include "../SapphireGLExtra/opengl_shape.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

#ifdef _WIN32
#include <malloc.h>
#elif defined __linux__ || defined __FreeBSD__ || defined __APPLE__
#include <alloca.h>
#else
#define SAPPHIRESG_DISABLE_ALLOCA 1
#endif

#define COLOR_COMPONENTS 4
#define COLOR_TYPE_SIZE 1
#define COLOR_SIZE 4

#define COORD_COMPONENTS 3
#define COORD_TYPE_SIZE sizeof(float)
#define COORD_SIZE (COLOR_COMPONENTS * COORD_TYPE_SIZE)

#define TEX_COORD_COMPONENTS 2
#define TEX_COORD_TYPE_SIZE sizeof(float)
#define TEX_COORD_SIZE (TEX_COORD_COMPONENTS * TEX_COORD_TYPE_SIZE)

#define PREDEFINED_GL_MODES 5

static const unsigned gl_draw_mode[PREDEFINED_GL_MODES] = {
	GL_TRIANGLE_STRIP,
	GL_POINTS,
	GL_LINE_LOOP,
	GL_TRIANGLE_STRIP,
	GL_TRIANGLE_FAN
};

struct SapphireSG_ShapeGuts *OpenGLSG_CreateShape(struct SapphireSG_Context *ctx) {
	struct SapphireSG_ShapeGuts *guts = malloc(sizeof(struct SapphireSG_ShapeGuts));

	glGenBuffers(3, guts->buffer);

	return guts;

}

void OpenGLSG_DestroyShape(struct SapphireSG_Context *ctx, struct SapphireSG_Shape *shape) {
	assert(ctx);
	assert(shape);

	if (!shape)
		return;

	glDeleteBuffers(3, shape->guts->buffer);
	free(shape->guts);
}

void OpenGLSG_UpdateShape(struct SapphireSG_Context *ctx, struct SapphireSG_Shape *shape) {

	SapphireOpenGLExtra_UploadVertices(
		shape->guts->buffer[0], shape->guts->buffer[1], shape->guts->buffer[2],
		shape->vertices, shape->num_vertices);

}

void OpenGLSG_DrawShape(struct SapphireSG_Context *ctx, struct SapphireSG_Shape *shape) {

	if (shape->num_vertices == 0)
		return;

	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	

	glBindBuffer(GL_ARRAY_BUFFER, shape->guts->buffer[0]);
	glColorPointer(COLOR_COMPONENTS, GL_UNSIGNED_BYTE, 0, NULL);

	glBindBuffer(GL_ARRAY_BUFFER, shape->guts->buffer[1]);
	glVertexPointer(COORD_COMPONENTS, GL_FLOAT, 0, NULL);

	glBindBuffer(GL_ARRAY_BUFFER, shape->guts->buffer[2]);
	glTexCoordPointer(TEX_COORD_COMPONENTS, GL_FLOAT, 0, NULL);

	if(shape->num_vertices < PREDEFINED_GL_MODES)
		glDrawArrays(gl_draw_mode[shape->num_vertices], 0, shape->num_vertices);
	else
		glDrawArrays(*gl_draw_mode, 0, shape->num_vertices);

	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

}
