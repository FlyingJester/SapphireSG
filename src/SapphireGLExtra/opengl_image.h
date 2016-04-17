#pragma once
#include "opengl.h"

GLuint SapphireOpenGLExtra_CreateImage(
	const unsigned char *pixels, unsigned long w, unsigned long h);

void SapphireOpenGLExtra_DestroyImage(GLuint);

void SapphireOpenGLExtra_BindImage(GLuint);
