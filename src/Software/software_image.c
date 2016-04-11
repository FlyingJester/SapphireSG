#include "software_image.h"
#include <string.h>

struct SapphireSG_ImageGuts *SoftwareSG_CreateImage(struct SapphireSG_Context *ctx,
	const unsigned char *pixels, unsigned long w, unsigned long h) {

	struct SapphireSG_ImageGuts *const im = malloc(sizeof(struct SapphireSG_ImageGuts));
	const unsigned long pix_size = (w * h) << 2;

	im->pixels = malloc(pix_size);
	memcpy(im->pixels, pixels, pix_size);

	return im;
}

void SoftwareSG_DestroyImage(struct SapphireSG_Context *ctx, struct SapphireSG_Image *im) {
	free(im->guts->pixels);
	free(im->guts);

	if (ctx->guts->image == im)
		ctx->guts->image = NULL;
}

void SoftwareSG_BindImage(struct SapphireSG_Context *ctx, struct SapphireSG_Image *im) {
	ctx->guts->image = im;
}
