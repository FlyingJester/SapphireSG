#pragma once
#include "../backend.h"
#include "software_context.h"

struct SapphireSG_ImageGuts {
	unsigned char *pixels;
};

struct SapphireSG_ImageGuts *SoftwareSG_CreateImage(struct SapphireSG_Context *ctx,
	const unsigned char *pixels, unsigned long w, unsigned long h);

void SoftwareSG_DestroyImage(struct SapphireSG_Context *ctx, struct SapphireSG_Image *im);

void SoftwareSG_BindImage(struct SapphireSG_Context *ctx, struct SapphireSG_Image *im);
