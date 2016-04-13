#include "opengl_shape.h"
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

void OpenGLSG_UpdateShape(struct SapphireSG_Context *ctx, struct SapphireSG_Shape *shape) {
	
	const unsigned long len = shape->num_vertices,
		len0 = len * COLOR_SIZE,
		len1 = len * COORD_SIZE,
		len2 = len * TEX_COORD_SIZE;
#ifndef SAPPHIRESG_DISABLE_ALLOCA
	const bool use_alloc = len < 32;
	unsigned char *const buffer0 = use_alloc ? alloca(len0) : malloc(len0);
	float *const buffer1 = use_alloc ? alloca(len1) : malloc(len1);
	float *const buffer2 = use_alloc ? alloca(len2) : malloc(len2);
#else
	unsigned char *const buffer0 = malloc(len0);
	float *const buffer1 = malloc(len1);
	float *const buffer2 = malloc(len2);
#endif
	
	unsigned long i = 0;

	while (i < shape->num_vertices) {
		buffer0[(i * 4) + 0] = shape->vertices[i].color[0];
		buffer0[(i * 4) + 1] = shape->vertices[i].color[1];
		buffer0[(i * 4) + 2] = shape->vertices[i].color[2];
		buffer0[(i * 4) + 3] = shape->vertices[i].color[3];

		buffer1[(i * 3) + 0] = shape->vertices[i].data[0];
		buffer1[(i * 3) + 1] = shape->vertices[i].data[1];
		buffer1[(i * 3) + 2] = shape->vertices[i].data[2];

		buffer2[(i * 2) + 0] = shape->vertices[i].data[0];
		buffer2[(i * 2) + 1] = shape->vertices[i].data[1];

		i++;
	}

	glBindBuffer(GL_ARRAY_BUFFER, shape->guts->buffer[0]);
	glBufferData(GL_ARRAY_BUFFER, len0, buffer0, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, shape->guts->buffer[1]);
	glBufferData(GL_ARRAY_BUFFER, len1, buffer1, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, shape->guts->buffer[2]);
	glBufferData(GL_ARRAY_BUFFER, len2, buffer2, GL_STATIC_DRAW);

	glFinish();

#ifndef SAPPHIRESG_DISABLE_ALLOCA
	if (!use_alloc) {
		free(buffer0);
		free(buffer1);
		free(buffer2);
	}
#else

	free(buffer0);
	free(buffer1);
	free(buffer2);
#endif
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
		glDrawArrays(gl_draw_mode[shape->num_vertices], 0, 3);
	else
		glDrawArrays(*gl_draw_mode, 0, 2);

	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

}
