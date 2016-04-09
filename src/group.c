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
		if (!SG_DrawShape(ctx, &group->shapes[i]))
			ok = false;
		i++;
	}

	return ok;
}
