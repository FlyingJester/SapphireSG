#include "opengl_shape.h"
#include <stdlib.h>
#include <stdbool.h>
#include <malloc.h>

#define PREDEFINED_GL_MODES 5

/**
 * Each vertex is four bytes for the color (r, g, b, a),
 * and five floats for the coords (x, y, z, u, v).
 * Bytewise, it is defined as so:
 * Byte:	0 | 1 | 2 | 3 |  4-7  |  8-11 | 12-15 | 16-19 | 20-23 |
 * Meaning: R | G | B | A |   X   |   Y   |   Z   |   U   |   V   |
 * Type:    UB| UB| UB| UB| Float | Float | Float | Float | Float |
 */

#define COLOR_COMPONENTS 4
#define VERTEX_SIZE (COLOR_COMPONENTS + (5 * sizeof(float)))

#define COLOR_SIZE (COLOR_COMPONENTS * 1)
#define COORD_SIZE (3 * sizeof(float))
#define TEX_COORD_SIZE (2 * sizeof(float))

#define COLOR_OFFSET 0
#define COLOR_STRIDE (VERTEX_SIZE - COLOR_SIZE)

#define COORD_OFFSET COLOR_SIZE
#define COORD_STRIDE (VERTEX_SIZE - COLOR_SIZE)

#define TEX_COORD_OFFSET (COLOR_SIZE + COORD_SIZE)
#define TEX_COORD_STRIDE (VERTEX_SIZE - TEX_COORD_SIZE)

static const unsigned gl_draw_mode[PREDEFINED_GL_MODES] = {
	GL_TRIANGLE_STRIP,
	GL_POINTS,
	GL_LINE_LOOP,
	GL_TRIANGLE_STRIP,
	GL_TRIANGLE_FAN
};

struct SapphireSG_ShapeGuts *OpenGLSG_CreateShape(struct SapphireSG_Context *ctx) {
	struct SapphireSG_ShapeGuts *guts = malloc(sizeof(struct SapphireSG_ShapeGuts));

	glGenBuffers(1, &guts->buffer);

	return guts;

}

void OpenGLSG_UpdateShape(struct SapphireSG_Context *ctx, struct SapphireSG_Shape *shape) {
	
	const unsigned long len = shape->num_vertices * VERTEX_SIZE;
#ifndef SAPPHIRESG_DISABLE_ALLOCA
	const bool use_alloc = len < 1024;
	unsigned char *const buffer = use_alloc ? alloca(len) : malloc(len);
#else
	unsigned char *const buffer = malloc(len);
#endif
	
	unsigned long i = 0;

	while (i < shape->num_vertices) {
		memcpy(buffer + (i*VERTEX_SIZE), shape->vertices[i].color, COLOR_SIZE);
		memcpy(buffer + (i*VERTEX_SIZE) + COORD_OFFSET, shape->vertices[i].data, COORD_SIZE + TEX_COORD_SIZE);
		i++;
	}

	glBufferData(GL_ARRAY_BUFFER, len, buffer, GL_STATIC_DRAW);

#ifndef SAPPHIRESG_DISABLE_ALLOCA
	if (!use_alloc)
		free(buffer);
#else
	free(buffer);
#endif
}

void OpenGLSG_DrawShape(struct SapphireSG_Context *ctx, struct SapphireSG_Shape *shape) {

	if (shape->num_vertices == 0)
		return;

/*	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
*/
	glBindBuffer(GL_ARRAY_BUFFER, shape->guts->buffer);
	
	glColorPointer(4, GL_UNSIGNED_BYTE, COLOR_STRIDE, NULL);
	glVertexPointer(3, GL_FLOAT, COORD_STRIDE, (unsigned char *)COORD_OFFSET);
	glTexCoordPointer(2, GL_FLOAT, TEX_COORD_STRIDE, (unsigned char *)TEX_COORD_OFFSET);

	if(shape->num_vertices < PREDEFINED_GL_MODES)
		glDrawArrays(gl_draw_mode[shape->num_vertices], 0, 2);
	else
		glDrawArrays(*gl_draw_mode, 0, 2);

/*	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
*/

}