#pragma once
#include "../SapphireGLExtra/opengl.h"
#include "../backend.h"

struct SapphireSG_ShapeGuts {
	GLuint buffer[3];
	GLuint vao;
};

struct SapphireSG_ShapeGuts *OpenGL4SG_CreateShape(struct SapphireSG_Context *ctx);
void OpenGL4SG_UpdateShape(struct SapphireSG_Context *ctx, struct SapphireSG_Shape *shape);
void OpenGL4SG_DrawShape(struct SapphireSG_Context *ctx, struct SapphireSG_Shape *shape);
