#pragma once
#include "../SapphireGLExtra/opengl.h"
#include "../backend.h"

struct SapphireSG_ShaderGuts {

	GLuint vert_shader, frag_shader;
	GLuint program;

	/* Uniform Locations */
	GLuint offset, rot_offset, angle, scale, screen_size, screen_origin;
	/* Vertex Attributes*/
	GLuint color, vertex_position;

};

struct SapphireSG_ShaderGuts *OpenGL4SG_CreateShader(struct SapphireSG_Context *ctx);
struct SapphireSG_ShaderGuts *OpenGL4SG_DestroyShader(struct SapphireSG_Context *ctx, struct SapphireSG_Shader* shader);
void OpenGL4SG_SetShaderParams(struct SapphireSG_Context *ctx, struct SapphireSG_Shader *shader,
	const struct SapphireSG_GroupAttribs *attribs);

