#include "opengl_context.h"
#include "opengl.h"
#include <stdlib.h>

struct SapphireSG_ContextGuts *OpenGLSG_CreateContext() {
	struct SapphireSG_ContextGuts *const guts = malloc(sizeof(struct SapphireSG_ContextGuts));
	guts->major = 2;
	guts->minor = 0;

	OpenGLSG_LoadGLFunctions(NULL);

	return guts;
}

void OpenGLSG_SetCoordinateSpace(const struct SapphireSG_Context *ctx, unsigned w, unsigned h,
	float left, float right, float top, float bottom, float nearz, float farz) {

	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(left, right, bottom, top, nearz, farz);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}