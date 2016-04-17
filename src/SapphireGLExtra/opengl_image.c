#include "opengl_image.h"
#include <assert.h>


GLuint SapphireOpenGLExtra_CreateImage(
	const unsigned char *pixels, unsigned long w, unsigned long h){

	GLuint texture = 0u;

	assert(pixels || !(w && h));

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

#ifdef __APPLE__
	/* Janky OS X Texture uploads... */
	glFinish();
#endif

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glGenerateMipmap(GL_TEXTURE_2D);

	return texture;
}

void SapphireOpenGLExtra_DestroyImage(GLuint texture) {
	glDeleteTextures(1, &texture);
}

void SapphireOpenGLExtra_BindImage(GLuint texture) {
	glBindTexture(GL_TEXTURE_2D, texture);
}
