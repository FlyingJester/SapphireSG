#include "opengl4_shader.h"
#include "opengl4_context.h"
#include <assert.h>

static void gl4_AppendShaders(struct OpenGL4SG_ShaderList *const shaders, struct OpenGL4SG_ShaderList *const shader) {
	if (shaders->next == NULL)
		shaders->next = shader;
	else
		gl4_AppendShaders(shaders->next, shader);
}

struct SapphireSG_ShaderGuts *OpenGL4SG_CreateShader(struct SapphireSG_Context *ctx) {
	struct OpenGL4SG_ShaderList *const shader = calloc(sizeof(struct OpenGL4SG_ShaderList), 1);

	assert(ctx);
	assert(shader);

	gl4_AppendShaders(ctx->guts->shaders, shader);

	return &shader->shader;
}

void OpenGL4SG_SetShaderParams(struct SapphireSG_Context *ctx, struct SapphireSG_Shader *shader,
	const struct SapphireSG_GroupAttribs *attribs) {
	
	assert(ctx);
	assert(shader);
	assert(attribs);

	glProgramUniform2f(shader->guts->program, shader->guts->offset, 
		attribs->offset_x, attribs->offset_y);
	glProgramUniform2f(shader->guts->program, shader->guts->rot_offset,
		attribs->rot_offset_x, attribs->rot_offset_y);
	glProgramUniform1f(shader->guts->program, shader->guts->angle, attribs->angle);
	glProgramUniform1f(shader->guts->program, shader->guts->scale, attribs->scale);

}
