#pragma once
#include "../SapphireGLExtra/opengl.h"
#include "../backend.h"

struct SapphireSG_ShapeGuts {
	GLuint buffer[3];
};

struct SapphireSG_ShapeGuts *OpenGLSG_CreateShape(struct SapphireSG_Context *ctx);
void OpenGLSG_UpdateShape(struct SapphireSG_Context *ctx, struct SapphireSG_Shape *shape);
void OpenGLSG_DrawShape(struct SapphireSG_Context *ctx, struct SapphireSG_Shape *shape);
