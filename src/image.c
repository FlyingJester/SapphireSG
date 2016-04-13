#include "image.h"
#include "backend.h"
#include <assert.h>
#include <stdlib.h>

SAPPHIRESG_API_EXPORT
struct SapphireSG_Image *SG_CreateImage(struct SapphireSG_Context *ctx, const unsigned char *pixels, unsigned w, unsigned h) {
	struct SapphireSG_Image *const image = malloc(sizeof(struct SapphireSG_Image));
	struct SapphireSG_ImageGuts *const guts = ctx->CreateImage(ctx, pixels, w, h);
	
	assert(ctx);
    assert(pixels);

	if (!(image && guts))
		return NULL;

	image->guts = guts;

	image->w = w;
	image->h = h;

	return image;
}

SAPPHIRESG_API_EXPORT
struct SapphireSG_Image *SG_CreateSolidColorImageV(struct SapphireSG_Context *ctx, const unsigned char *rgba) {
	if(rgba)
		return SG_CreateImage(ctx, rgba, 1, 1);
	else
		return SG_CreateSolidColorImage(ctx, 0, 0, 0, 0xFF);

}

SAPPHIRESG_API_EXPORT
struct SapphireSG_Image *SG_CreateSolidColorImage(struct SapphireSG_Context *ctx,
	unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
	unsigned char rgba[4];

	rgba[0] = r;
	rgba[1] = g;
	rgba[2] = b;
	rgba[3] = a;

	return SG_CreateImage(ctx, rgba, 1, 1);
}

SAPPHIRESG_API_EXPORT
bool SG_DestroyImage(struct SapphireSG_Context *ctx, struct SapphireSG_Image *im) {
	assert(ctx);
	assert(im);

	if (!im)
		return false;

	ctx->DestroyImage(ctx, im);
	free(im);

	return true;
}

SAPPHIRESG_API_EXPORT
bool SG_GetImageSize(struct SapphireSG_Context *ctx, const struct SapphireSG_Image *im, unsigned *w, unsigned *h) {
    assert(ctx);
    assert(im);

    if (w)
        w[0] = im->w;
    if (h)
        h[0] = im->h;

    return true;
}

SAPPHIRESG_API_EXPORT
unsigned SG_GetImageWidth(struct SapphireSG_Context *ctx, const struct SapphireSG_Image *im) {
    assert(ctx);
    assert(im);

    return im->w;
}

SAPPHIRESG_API_EXPORT
unsigned SG_GetImageHeight(struct SapphireSG_Context *ctx, const struct SapphireSG_Image *im) {
    assert(ctx);
    assert(im);

    return im->h;
}
