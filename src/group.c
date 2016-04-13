#include "group.h"
#include "shape.h"
#include <assert.h>

SAPPHIRESG_API_EXPORT
bool SG_DrawGroup(struct SapphireSG_Context *ctx, struct SapphireSG_Group *group) {
	unsigned long i = 0;
	bool ok = true;
	
	assert(ctx);
	assert(group);

	while (i < group->num_shapes) {
		if (!SG_DrawShape(ctx, group->shapes[i]))
			ok = false;
		i++;
	}

	return ok;
}

SAPPHIRESG_API_EXPORT
struct SapphireSG_Group *SG_CreateGroup(struct SapphireSG_Context *ctx) {
	assert(ctx);

	{
		struct SapphireSG_Group *const group = malloc(sizeof(struct SapphireSG_Group));
		group->num_shapes = 0;

		group->shapes_capacity = 16;
		group->shapes = malloc(0x100);

		return group;
	}
}

SAPPHIRESG_API_EXPORT
bool SG_SetGroupShapeCapacity(struct SapphireSG_Context *ctx, struct SapphireSG_Group *group, unsigned n) {

	assert(ctx);
	assert(group);

	if (group->shapes_capacity < n) {

		do{
			group->shapes_capacity <<= 1;
		} while (group->shapes_capacity < n);

		group->shapes = realloc(group->shapes, 
			group->shapes_capacity * sizeof(struct SapphireSG_Shape *));
	}
	else if (group->shapes_capacity >> 3 > n) {
		group->shapes_capacity >>= 3;

		group->shapes = realloc(group->shapes, 
			group->shapes_capacity * sizeof(struct SapphireSG_Shape *));

	}

	group->num_shapes = n;
	return true;
}

SAPPHIRESG_API_EXPORT
unsigned SG_GetGroupShapeCapacity(struct SapphireSG_Context *ctx, struct SapphireSG_Group *group) {

	assert(ctx);
	assert(group);

	return group->num_shapes;
}

SAPPHIRESG_API_EXPORT
bool SG_SetGroupShape(struct SapphireSG_Context *ctx, struct SapphireSG_Group *group, unsigned i, struct SapphireSG_Shape *shape) {

	assert(ctx);
	assert(group);
	assert(i < group->num_shapes);

	group->shapes[i] = shape;

	return true;

}

SAPPHIRESG_API_EXPORT
struct SapphireSG_Shape *SG_GetGroupShape(struct SapphireSG_Context *ctx, struct SapphireSG_Group *group, unsigned i) {


	assert(ctx);
	assert(group);
	assert(i < group->num_shapes);

	return group->shapes[i];

}
