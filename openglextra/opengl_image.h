#pragma once
#include "opengl.h"

#ifdef __cplusplus
extern "C" {
#endif

GLuint OpenGLExtra_CreateImage(
	const unsigned char *pixels, unsigned long w, unsigned long h);

void OpenGLExtra_UploadImage(
	GLuint name, const unsigned char *pixels, unsigned long w, unsigned long h);
    
void OpenGLExtra_ReadImage(
	GLuint name, unsigned char *pixels, unsigned long w, unsigned long h);

void OpenGLExtra_DestroyImage(GLuint);

void OpenGLExtra_BindImage(GLuint);

#ifdef __cplusplus
}
#endif
