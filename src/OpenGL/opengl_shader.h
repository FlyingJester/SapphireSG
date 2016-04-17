#pragma once
#include "../group.h"

struct SapphireSG_ShaderGuts {
	struct SapphireSG_GroupAttribs attribs;
};

struct SapphireSG_VertexShader { char _; };
struct SapphireSG_FragmentShader { char _; };

struct SapphireSG_VertexShader *OpenGLSG_CreateVertexShader(struct SapphireSG_Context *ctx);
struct SapphireSG_FragmentShader *OpenGLSG_CreateFragmentShader(struct SapphireSG_Context *ctx);
struct SapphireSG_ShaderGuts *OpenGLSG_CreateShader(struct SapphireSG_Context *ctx,
	struct SapphireSG_VertexShader *, struct SapphireSG_FragmentShader *);
struct SapphireSG_ShaderGuts *OpenGLSG_GetDefaultShader(struct SapphireSG_Context *ctx);
void OpenGLSG_DestroyShader(struct SapphireSG_Context *ctx, struct SapphireSG_Shader* shader);
void OpenGLSG_DestroyVertexShader(struct SapphireSG_Context *ctx, struct SapphireSG_VertexShader *v);
void OpenGLSG_DestroyFragmentShader(struct SapphireSG_Context *ctx, struct SapphireSG_FragmentShader *f);
void OpenGLSG_SetShaderParams(struct SapphireSG_Context *ctx, struct SapphireSG_Shader *shader,
	const struct SapphireSG_GroupAttribs *attribs);
