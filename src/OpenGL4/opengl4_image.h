#pragma once
#include "../SapphireGLExtra/opengl.h"
#include "../backend.h"

struct SapphireSG_ImageGuts {
	GLuint texture;
};

struct SapphireSG_ImageGuts *OpenGL4SG_CreateImage(struct SapphireSG_Context *ctx,
	const unsigned char *pixels, unsigned long w, unsigned long h);
void OpenGL4SG_DestroyImage(struct SapphireSG_Context *ctx, struct SapphireSG_Image *im);

void OpenGL4SG_BindImage(struct SapphireSG_Context *ctx, struct SapphireSG_Image *im);
