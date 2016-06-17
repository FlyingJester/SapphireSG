#include "opengl_image.h"
#include <assert.h>


GLuint OpenGLExtra_CreateImage(
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

void OpenGLExtra_UploadImage(
	GLuint name, const unsigned char *pixels, unsigned long w, unsigned long h){
    
	glBindTexture(GL_TEXTURE_2D, name);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
	glGenerateMipmap(GL_TEXTURE_2D);
}

void OpenGLExtra_ReadImage(
	GLuint name, unsigned char *pixels, unsigned long w, unsigned long h){
    
    assert(name);
    assert(pixels);
    
	glBindTexture(GL_TEXTURE_2D, name);
    glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
}

void OpenGLExtra_DestroyImage(GLuint texture) {
    if(texture > 0u)
        glDeleteTextures(1, &texture);
}

void OpenGLExtra_BindImage(GLuint texture) {
	glBindTexture(GL_TEXTURE_2D, texture);
}
