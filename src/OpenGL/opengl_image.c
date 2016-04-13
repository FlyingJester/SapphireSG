#include "opengl_image.h"
#include <assert.h>

struct SapphireSG_ImageGuts *OpenGLSG_CreateImage(struct SapphireSG_Context *ctx,
	const unsigned char *pixels, unsigned long w, unsigned long h) {
	struct SapphireSG_ImageGuts *const guts = malloc(sizeof(struct SapphireSG_ImageGuts));

	assert(ctx);
	assert(pixels || !(w && h));

	glGenTextures(1, &guts->texture);
	glBindTexture(GL_TEXTURE_2D, guts->texture);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

#ifdef __APPLE__
	/* Janky OS X Texture uploads... */
	glFinish();
#endif

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

/*	glGenerateMipmap(GL_TEXTURE_2D); */

	return guts;
}

void OpenGLSG_DestroyImage(struct SapphireSG_Context *ctx, struct SapphireSG_Image *im) {
	glDeleteTextures(1, &im->guts->texture);
	free(im->guts);
}

void OpenGLSG_BindImage(struct SapphireSG_Context *ctx, struct SapphireSG_Image *im) {
	assert(ctx);
	assert(im);
	glBindTexture(GL_TEXTURE_2D, im->guts->texture);
}
