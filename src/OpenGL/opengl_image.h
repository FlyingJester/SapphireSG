#pragma once
#include "opengl.h"
#include "../backend.h"

struct SapphireSG_ImageGuts {
	GLuint texture;
};

struct SapphireSG_ImageGuts *OpenGLSG_CreateImage(struct SapphireSG_Context *ctx,
	const unsigned char *pixels, unsigned long w, unsigned long h);
void OpenGLSG_DestroyImage(struct SapphireSG_Context *ctx, struct SapphireSG_Image *im);

void OpenGLSG_BindImage(struct SapphireSG_Context *ctx, struct SapphireSG_Image *im);
