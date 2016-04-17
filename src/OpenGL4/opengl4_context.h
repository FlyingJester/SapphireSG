#pragma once
#include "opengl4_shader.h"
#include "../context.h"
#include "../SapphireGLExtra/opengl.h"


struct OpenGL4SG_ShaderList {
	struct OpenGL4SG_ShaderGuts shader;
	struct OpenGL4SG_ShaderList *next;
};

struct SapphireSG_ContextGuts {
	float left, right, top, bottom;
	struct OpenGL4SG_ShaderList *shaders;
};

struct SapphireSG_ContextGuts *OpenGL4SG_CreateContext();
void OpenGL4SG_SetCoordinateSpace(const struct SapphireSG_Context *ctx, unsigned w, unsigned h,
	float left, float right, float top, float bottom, float nearz, float farz);
