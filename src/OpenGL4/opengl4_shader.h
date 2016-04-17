#pragma once
#include "../SapphireGLExtra/opengl.h"

struct OpenGL4SG_ShaderGuts {

	GLuint vert_shader, frag_shader;
	GLuint program;

	/* Uniform Locations */
	GLuint offset, rot_offset, angle, scale, screen_size, screen_origin;
	/* Vertex Attributes*/
	GLuint color, vertex_position;

};

void OpenGL4SG_SetCoordinateSpace(const struct SapphireSG_Context *ctx, unsigned w, unsigned h,
	float left, float right, float top, float bottom, float nearz, float farz);

struct OpenGL4SG_ShaderGuts *OpenGL4SG_CreateShader();
