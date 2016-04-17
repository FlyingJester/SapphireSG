#pragma once
#include "opengl.h"

#define COLOR_COMPONENTS 4
#define COLOR_TYPE_SIZE 1
#define COLOR_SIZE 4

#define COORD_COMPONENTS 3
#define COORD_TYPE_SIZE sizeof(float)
#define COORD_SIZE (COLOR_COMPONENTS * COORD_TYPE_SIZE)

#define TEX_COORD_COMPONENTS 2
#define TEX_COORD_TYPE_SIZE sizeof(float)
#define TEX_COORD_SIZE (TEX_COORD_COMPONENTS * TEX_COORD_TYPE_SIZE)

void SapphireOpenGLExtra_UploadVertices(
	GLuint glbuffer1, GLuint glbuffer2, GLuint glbuffer3,
	const struct SapphireSG_Vertex *vertices, const unsigned long num_vertices);
