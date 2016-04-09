#include "opengl_context.h"
#include <stdlib.h>

struct SapphireSG_ContextGuts *OpenGLSG_CreateContext() {
	struct SapphireSG_ContextGuts *const guts = malloc(sizeof(struct SapphireSG_ContextGuts));
	guts->major = 2;
	guts->minor = 0;

	return guts;
}