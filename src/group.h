#pragma once
#include "sapphire_sg.h"

struct SapphireSG_ShaderGuts;

struct SapphireSG_Shader {
	struct SapphireSG_ShaderGuts *guts;
};

struct SapphireSG_GroupAttribs {
	float offset_x, offset_y, 
		rot_offset_x, rot_offset_y, 
		angle, scale;
};

struct SapphireSG_Group {

	struct SapphireSG_GroupAttribs attribs;

	struct SapphireSG_Shader *shader;

	unsigned long num_shapes, shapes_capacity;
	struct SapphireSG_Shape **shapes;

};
