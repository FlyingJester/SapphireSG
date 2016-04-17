#include "opengl4_backend.h"
#include "opengl4_context.h"
#include "opengl4_shape.h"
#include "opengl4_image.h"
#include <assert.h>

void OpenGL4SG_InitContext(struct SapphireSG_Context *ctx) {

	assert(ctx);

	GENERIC_CTX_INIT(ctx, OpenGL4SG);

}