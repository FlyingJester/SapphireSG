#pragma once
#include "../SapphireGLExtra/opengl.h"
#include "../backend.h"

struct SapphireSG_ShaderGuts {

	GLuint program;

	/* Uniform Locations */
	GLuint offset, rot_offset, angle, scale, screen_size, screen_origin;
	/* Vertex Attributes*/
	GLuint color, vertex_position;

};

struct SapphireSG_VertexShader {
	GLuint shader;
};

struct SapphireSG_FragmentShader {
	GLuint shader;
};

struct SapphireSG_VertexShader *OpenGL4SG_CreateVertexShader(struct SapphireSG_Context *ctx, char *log, unsigned long len);
struct SapphireSG_FragmentShader *OpenGL4SG_CreateFragmentShader(struct SapphireSG_Context *ctx, char *log, unsigned long len);
struct SapphireSG_ShaderGuts *OpenGL4SG_GetDefaultShader(struct SapphireSG_Context *ctx);
struct SapphireSG_ShaderGuts *OpenGL4SG_CreateShader(struct SapphireSG_Context *ctx,
	struct SapphireSG_VertexShader *v, struct SapphireSG_FragmentShader *f, char *log, unsigned long len);
void OpenGL4SG_DestroyShader(struct SapphireSG_Context *ctx, struct SapphireSG_Shader* shader);
void OpenGL4SG_SetShaderParams(struct SapphireSG_Context *ctx, struct SapphireSG_Shader *shader,
	const struct SapphireSG_GroupAttribs *attribs);
void OpenGL4SG_DestroyVertexShader(struct SapphireSG_Context *ctx, struct SapphireSG_VertexShader *v);
void OpenGL4SG_DestroyFragmentShader(struct SapphireSG_Context *ctx, struct SapphireSG_FragmentShader *f);

void OpenGL4SG_BindShader(struct SapphireSG_Context *ctx, struct SapphireSG_Shader* shader);
void OpenGL4SG_UnbindShader(struct SapphireSG_Context *ctx, struct SapphireSG_Shader* shader);