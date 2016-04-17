#include "opengl_shader.h"
#include "../SapphireGLExtra/opengl.h"
#include <assert.h>
#include <string.h>

struct SapphireSG_VertexShader *OpenGLSG_CreateVertexShader(struct SapphireSG_Context *ctx, char *log, unsigned long len) {
	assert(ctx);

	if (log && len)
		log[0] = '\0';

	return (void *)0xabc;
}

struct SapphireSG_FragmentShader *OpenGLSG_CreateFragmentShader(struct SapphireSG_Context *ctx, char *log, unsigned long len) {
	assert(ctx);

	if (log && len)
		log[0] = '\0';

	return (void *)0xdef;
}

struct SapphireSG_ShaderGuts *OpenGLSG_CreateShader(struct SapphireSG_Context *ctx,
	struct SapphireSG_VertexShader *v, struct SapphireSG_FragmentShader *f, char *log, unsigned long len) {

	assert(ctx);
	assert(v == (void *)0xabc);
	assert(f == (void *)0xdef);

	if (log && len)
		log[0] = '\0';

	return OpenGLSG_GetDefaultShader(ctx);
}

struct SapphireSG_ShaderGuts *OpenGLSG_GetDefaultShader(struct SapphireSG_Context *ctx) {
	struct SapphireSG_ShaderGuts *const guts = calloc(sizeof(struct SapphireSG_ShaderGuts), 1);

	assert(guts);
	assert(ctx);

	return guts;
}

void OpenGLSG_DestroyShader(struct SapphireSG_Context *ctx, struct SapphireSG_Shader* shader) {
	assert(shader);
	assert(ctx);

	free(shader->guts);
}

void OpenGLSG_SetShaderParams(struct SapphireSG_Context *ctx, struct SapphireSG_Shader *shader,
	const struct SapphireSG_GroupAttribs *attribs) {
	assert(shader);
	assert(ctx);
	assert(attribs);

	memcpy(&shader->guts->attribs, attribs, sizeof(struct SapphireSG_GroupAttribs));
}

void OpenGLSG_DestroyVertexShader(struct SapphireSG_Context *ctx, struct SapphireSG_VertexShader *v) {
	assert(ctx);
	assert(v == (void *)0xabc);
}

void OpenGLSG_DestroyFragmentShader(struct SapphireSG_Context *ctx, struct SapphireSG_FragmentShader *f) {
	assert(ctx);
	assert(f == (void *)0xdef);
}

void OpenGLSG_BindShader(struct SapphireSG_Context *ctx, struct SapphireSG_Shader* shader) {
	glPushMatrix();

	glTranslatef(shader->guts->attribs.offset_x, shader->guts->attribs.offset_y, 0.0f);
	glRotatef(shader->guts->attribs.angle, 
		shader->guts->attribs.rot_offset_x, shader->guts->attribs.rot_offset_y, 0.0f);

}

void OpenGLSG_UnbindShader(struct SapphireSG_Context *ctx, struct SapphireSG_Shader* shader) {
	glPopMatrix();
}
