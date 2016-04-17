#include "opengl4_shader.h"
#include "opengl4_context.h"
#include <assert.h>

static const char *const s_default_vertex_source =
"#version 410\n"
"\n"
"uniform vec2 sapphire_offset;\n"
"uniform vec2 sapphire_rot_offset;\n"
"uniform float sapphire_rot_angle;\n"
"\n"
"in vec2 sapphire_texture_uv;\n"
"in vec4 sapphire_position;\n"
"in vec4 sapphire_color;\n"
"\n"
"out vec4 color_v;\n"
"out vec2 tex_v;\n"
"\n"
"uniform vec2 sapphire_screen_size;\n"
"\n"
"vec2 Sapphire_ApplyRotation(vec2 a_position, vec2 a_offset, float a_angle){\n"
"    vec2 l_offset = (a_position - a_offset);\n"
"    if(l_offset.x==0){\n"
"		l_offset.x = -0.1\n"
"    }\n"
"    \n"
"    float l_modangle = atan(l_offset.y, l_offset.x) + a_angle;\n"
"    l_offset *= l_offset;\n"
"    float l_distance = sqrt(l_offset.x + l_offset.y);\n"
"    return (a_offset + (vec2(cos(l_modangle), sin(l_modangle)) * l_distance));\n"
"}\n"
"\n"
"void main(void){\n"
"    // Passthroughs\n"
"    tex_v = sapphire_texture_uv;\n"
"    color_v = sapphire_color;\n"
"    \n"
"    // Calculate rotation\n"
"    vec4 l_new_position = sapphire_position;\n"
"    l_new_position.xy = Sapphire_ApplyRotation(sapphire_position.xy, sapphire_rot_offset, sapphire_rot_angle);\n"
"    vec4 l_new_position_double = l_new_position*2.0;\n"
"    \n"
"    // Sadly, I do not remember exactly what this does from TurboSphere\n"
"    gl_Position = (vec4(sapphire_offset.x*2.0, sapphire_offset.y*(-2.0), 0.0, 0.0) + (vec4(l_new_position_double.x - sapphire_screen_size.x, -l_new_position_double.y + sapphire_screen_size.y, l_new_position.ba))) / "
"        vec4(sapphire_screen_size, 1.0, 1.0);\n"
"    "
"    "
"    "
"}\n"
"\n";

static const char *const s_default_fragment_source =
"#version 410\n"
"\n"
"in vec4 color_v;\n"
"in vec2 tex_v;\n"
"out vec4 frag_color;\n"
"\n"
"uniform sampler2D tex_dat;\n"
"\n"
"void main(void){\n"
"frag_color = color_v * texture(tex_dat, tex_v);\n"
"}\n"
"\n";

static void gl4_AppendShaders(struct OpenGL4SG_ShaderList *const shaders, struct OpenGL4SG_ShaderList *const shader) {
	if (shaders->next == NULL)
		shaders->next = shader;
	else
		gl4_AppendShaders(shaders->next, shader);
}

struct SapphireSG_ShaderGuts *OpenGL4SG_CreateShader(struct SapphireSG_Context *ctx,
	struct SapphireSG_VertexShader *v, struct SapphireSG_FragmentShader *f, char *log, unsigned long len) {
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
