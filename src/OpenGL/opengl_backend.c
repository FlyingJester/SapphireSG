#include "opengl_backend.h"
#include "opengl_context.h"
#include "opengl_shape.h"
#include "opengl_image.h"
#include <assert.h>

void OpenGLSG_InitContext(struct SapphireSG_Context *ctx) {

	assert(ctx);

	ctx->CreateContext = OpenGLSG_CreateContext;
	ctx->SetCoordinateSpace = OpenGLSG_SetCoordinateSpace;
	ctx->CreateShape = OpenGLSG_CreateShape;
	ctx->CreateImage = OpenGLSG_CreateImage;
	ctx->DestroyImage = OpenGLSG_DestroyImage;
	ctx->BindImage = OpenGLSG_BindImage;
	ctx->DrawShape = OpenGLSG_DrawShape;
	ctx->UpdateShape = OpenGLSG_UpdateShape;

}