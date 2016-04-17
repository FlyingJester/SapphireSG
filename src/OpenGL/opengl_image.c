#include "opengl_image.h"
#include "../SapphireGLExtra/opengl_image.h"
#include <assert.h>

struct SapphireSG_ImageGuts *OpenGLSG_CreateImage(struct SapphireSG_Context *ctx,
	const unsigned char *pixels, unsigned long w, unsigned long h) {
	struct SapphireSG_ImageGuts *const guts = malloc(sizeof(struct SapphireSG_ImageGuts));

	assert(guts);

	guts->texture = SapphireOpenGLExtra_CreateImage(pixels, w, h);

	return guts;
}

void OpenGLSG_DestroyImage(struct SapphireSG_Context *ctx, struct SapphireSG_Image *im) {
	assert(ctx);
	assert(im);
	assert(im->guts);
	SapphireOpenGLExtra_DestroyImage(im->guts->texture);
	free(im->guts);
}

void OpenGLSG_BindImage(struct SapphireSG_Context *ctx, struct SapphireSG_Image *im) {
	assert(ctx);
	assert(im);
	assert(im->guts);
	SapphireOpenGLExtra_BindImage(im->guts->texture);
}
