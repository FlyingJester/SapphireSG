#include "opengl_shape.h"
#include "opengl.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include "../shape.h"

#ifdef _WIN32
#include <malloc.h>
#elif defined __linux__ || defined __FreeBSD__ || defined __APPLE__
#include <alloca.h>
#else
#define SAPPHIRESG_DISABLE_ALLOCA 1
#endif

void SapphireOpenGLExtra_UploadVertices(
	GLuint glbuffer1, GLuint glbuffer2, GLuint glbuffer3,
	const struct SapphireSG_Vertex *vertices, const unsigned long len) {

	const unsigned long len0 = len * COLOR_SIZE,
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

	while (i < len) {
		buffer0[(i * 4) + 0] = vertices[i].color[0];
		buffer0[(i * 4) + 1] = vertices[i].color[1];
		buffer0[(i * 4) + 2] = vertices[i].color[2];
		buffer0[(i * 4) + 3] = vertices[i].color[3];

		buffer1[(i * 3) + 0] = vertices[i].data[0];
		buffer1[(i * 3) + 1] = vertices[i].data[1];
		buffer1[(i * 3) + 2] = vertices[i].data[2];

		buffer2[(i * 2) + 0] = vertices[i].data[0];
		buffer2[(i * 2) + 1] = vertices[i].data[1];

		i++;
	}

	glBindBuffer(GL_ARRAY_BUFFER, glbuffer1);
	glBufferData(GL_ARRAY_BUFFER, len0, buffer0, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, glbuffer2);
	glBufferData(GL_ARRAY_BUFFER, len1, buffer1, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, glbuffer3);
	glBufferData(GL_ARRAY_BUFFER, len2, buffer2, GL_STATIC_DRAW);
	
	/* Doesn't seem to be necessary with Mesa, is this a bug? */
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
