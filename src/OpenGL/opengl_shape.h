#pragma once
#include "opengl.h"
#include "../backend.h"

struct SapphireSG_ShapeGuts {
	GLuint buffer;
};

struct SapphireSG_ShapeGuts *OpenGLSG_CreateShape(struct SapphireSG_Context *ctx);
void OpenGLSG_UpdateShape(struct SapphireSG_Context *ctx, struct SapphireSG_Shape *shape);
void OpenGLSG_DrawShape(struct SapphireSG_Context *ctx, struct SapphireSG_Shape *shape);

