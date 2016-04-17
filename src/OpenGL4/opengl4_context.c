#include "opengl4_context.h"
#include "../SapphireGLExtra/opengl.h"
#include <stdlib.h>
#include <math.h>

struct SapphireSG_ContextGuts *OpenGL4SG_CreateContext() {
	struct SapphireSG_ContextGuts *const guts = malloc(sizeof(struct SapphireSG_ContextGuts));

	guts->left = -1.0f;
	guts->right = 1.0f;
	guts->top = -1.0f;
	guts->bottom = 1.0f;
	guts->shaders = NULL;

	SapphireOpenGLExtra_LoadGLFunctions(NULL);

	return guts;
}

static void gl4_UpdateShaders(const struct OpenGL4SG_ShaderList *const shaders,
	const float w, const float h, const float x, const float y) {

	if (shaders == NULL)
		return;
	else {

		glProgramUniform2f(shaders->shader.program, shaders->shader.screen_size, w, h);
		glProgramUniform2f(shaders->shader.program, shaders->shader.screen_origin, x, y);

		gl4_UpdateShaders(shaders->next, w, h, x, y);
	}
}

void OpenGL4SG_SetCoordinateSpace(const struct SapphireSG_Context *ctx, unsigned w, unsigned h,
	float left, float right, float top, float bottom, float nearz, float farz) {

	const float shader_w = (float)fabs(ctx->guts->right - ctx->guts->left),
		shader_h = (float)fabs(ctx->guts->bottom - ctx->guts->top);

	ctx->guts->left = left;
	ctx->guts->right = right;
	ctx->guts->top = top;
	ctx->guts->bottom = bottom;

	gl4_UpdateShaders(ctx->guts->shaders, shader_w, shader_h, ctx->guts->left, ctx->guts->top);

}