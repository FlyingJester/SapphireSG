#include "context.h"
#include "sapphire_sg.h"

#include "OpenGL/opengl_backend.h"
#include "Software/software_backend.h"
#include "OpenGL4/opengl4_backend.h"

#include <assert.h>

#if (!defined _WIN32) && (!defined SAPPHIRESG_DISABLE_EGL) && (!defined SAPPHIRESG_ENABLE_EGL)
#define SAPPHIRESG_ENABLE_EGL
#endif

#ifdef _WIN32
#include "Windows.h"
#else
#include <dlfcn.h> 
#endif

#ifdef SAPPHIRESG_ENABLE_EGL
#include <EGL/egl.h>
#endif

SAPPHIRESG_API_EXPORT
struct SapphireSG_Context *SG_CreateContext(enum SG_Backend backend, unsigned maj, unsigned min) {
	struct SapphireSG_Context *const ctx = calloc(sizeof(struct SapphireSG_Context), 1);

	switch (backend) {
		case SG_OpenGL2:
			OpenGLSG_InitContext(ctx);
			break;
		case SG_OpenGL4:
			OpenGL4SG_InitContext(ctx);
			break;
		case SG_Software:
			SoftwareSG_InitContext(ctx);
	}
	ctx->guts = ctx->CreateContext();

	ctx->backend = backend;



	return ctx;
}

/* arg should be set to the DC */
SAPPHIRESG_API_EXPORT
void SG_WGLSceneEndCallback(struct SapphireSG_Context *ctx, void *arg) {
#ifdef _WIN32
	assert(sizeof(HDC) >= sizeof(void *));

	SwapBuffers((HDC)arg);

#endif
}

static void (*SG_SDL_GL_SwapWindow)(void *);
static void *sdl2_lib;

/* arg should be set to the SDL_Window */
SAPPHIRESG_API_EXPORT
void SG_SDL2SceneEndCallback(struct SapphireSG_Context *ctx, void *arg) {
	if (!SG_SDL_GL_SwapWindow){
		const char *const swap_window_name = "SDL_GL_SwapWindow";
#ifdef _WIN32
		if(!sdl2_lib)
			sdl2_lib = LoadLibraryA("SDL2.dll");

		SG_SDL_GL_SwapWindow = (void(*)(void *))GetProcAddress(sdl2_lib, swap_window_name);
#else
		if (!sdl2_lib)
			sdl2_lib = dlopen("SDL2", RTLD_NOW | RTLD_GLOBAL);

		SG_SDL_GL_SwapWindow = (void(*)(void *))dlsym(sdl2_lib, swap_window_name);
#endif
	}
	if(SG_SDL_GL_SwapWindow)
		SG_SDL_GL_SwapWindow(arg);
}

SAPPHIRESG_API_EXPORT
void SG_EGLSceneEndCallback(struct SapphireSG_Context *ctx, void *arg) {
#ifdef SAPPHIRESG_ENABLE_EGL
	eglSwapBuffers(eglGetCurrentDisplay(), (EGLSurface)arg);
#endif
}

SAPPHIRESG_API_EXPORT
void SG_SetCoordinateDistance(const struct SapphireSG_Context *ctx, unsigned w, unsigned h) {
	SG_SetCoordinateSpace(ctx, w, h, 0.0f, (float)w, 0.0f, (float)h, -1.0f, 1.0f);

}

SAPPHIRESG_API_EXPORT
void SG_SetCoordinateSpace(const struct SapphireSG_Context *ctx, unsigned w, unsigned h,
	float left, float right, float top, float bottom, float nearz, float farz) {
	ctx->SetCoordinateSpace(ctx, w, h, left, right, top, bottom, nearz, farz);
}
