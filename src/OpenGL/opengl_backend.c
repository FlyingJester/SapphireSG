#include "opengl_backend.h"
#include "opengl_context.h"
#include "opengl_shape.h"
#include "opengl_image.h"
#include "opengl_shader.h"
#include <assert.h>

void OpenGLSG_InitContext(struct SapphireSG_Context *ctx) {

	assert(ctx);

	GENERIC_CTX_INIT(ctx, OpenGLSG);

}