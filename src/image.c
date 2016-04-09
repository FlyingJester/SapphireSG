#include "image.h"
#include "backend.h"
#include <assert.h>

SAPPHIRESG_API_EXPORT
struct SapphireSG_Image *SG_CreateImage(struct SapphireSG_Context *ctx, const unsigned char *pixels, unsigned w, unsigned h) {
    assert(ctx);
    assert(pixels);
    return ctx->CreateImage(ctx, pixels, w, h);
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
