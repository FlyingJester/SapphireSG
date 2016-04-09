#include "opengl_image.h"

struct SapphireSG_ImageGuts *OpenGLSG_CreateImage(struct SapphireSG_Context *ctx,
	const unsigned char *pixels, unsigned long w, unsigned long h) {
	struct SapphireSG_ImageGuts *const guts = malloc(sizeof(struct SapphireSG_ImageGuts));

	glGenTextures(1, &guts->texture);
	glBindTexture(GL_TEXTURE_2D, guts->texture);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

#ifdef __APPLE__
	/* Janky OS X Texture uploads... */
	glFinish();
#endif

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	return guts;
}

void OpenGLSG_BindImage(struct SapphireSG_Context *ctx, struct SapphireSG_Image *im) {
	glBindTexture(GL_TEXTURE_2D, im->guts->texture);
}
