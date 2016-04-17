#include "opengl4_backend.h"
#include "opengl4_context.h"
#include "opengl4_shape.h"
#include "opengl4_image.h"
#include <assert.h>

void OpenGLSG_InitContext(struct SapphireSG_Context *ctx) {

	assert(ctx);

	ctx->CreateContext = OpenGL4SG_CreateContext;
	ctx->SetCoordinateSpace = OpenGL4SG_SetCoordinateSpace;
	ctx->CreateShape = OpenGL4SG_CreateShape;
	ctx->CreateImage = OpenGL4SG_CreateImage;
	ctx->DestroyImage = OpenGL4SG_DestroyImage;
	ctx->BindImage = OpenGL4SG_BindImage;
	ctx->DrawShape = OpenGL4SG_DrawShape;
	ctx->UpdateShape = OpenGL4SG_UpdateShape;

}