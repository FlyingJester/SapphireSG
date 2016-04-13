#pragma once
#include "sapphire_sg.h"

struct SapphireSG_Group {

	unsigned long num_shapes, shapes_capacity;
	struct SapphireSG_Shape **shapes;

};
