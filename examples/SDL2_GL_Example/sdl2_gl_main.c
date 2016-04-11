#include "../../src/sapphire_sg.h"

#ifdef _WIN32
#include "SDL2/SDL.h"
#include <Windows.h>
#undef main
#define main WinMain
#else
#include <SDL2/SDL.h>
#endif

#include <GL/gl.h>

struct WindowData {

	SDL_GLContext ctx, far_ctx;
	SDL_Window *window;

} data;

static void SetSDL2OpenGLAttribs() {

	SDL_GL_ResetAttributes();

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_SHARE_WITH_CURRENT_CONTEXT, 1);

}

static void scene_end_callback(struct SapphireSG_Context *ctx, void *arg) {
	struct WindowData *win_data = (struct WindowData *)arg;

	SDL_GL_SwapWindow(win_data->window);
	glClear(GL_COLOR_BUFFER_BIT);

}

static void init_gl_context(void *arg) {
	struct WindowData *win_data = (struct WindowData *)arg;
	SDL_GL_MakeCurrent(win_data->window, win_data->far_ctx);
}

int main(int argc, char *argv[]) {

	SDL_Init(SDL_INIT_VIDEO);

	SetSDL2OpenGLAttribs();

	data.window = SDL_CreateWindow("SDL2 GL SapphireSG example", 32, 32, 800, 600, SDL_WINDOW_OPENGL);

/* This will be used for multi-threaded rendering

	data.far_ctx = SDL_GL_CreateContext(data.window);
	SDL_GL_MakeCurrent(data.window, data.far_ctx);

*/

	SetSDL2OpenGLAttribs();
	data.ctx = SDL_GL_CreateContext(data.window);
	SDL_GL_MakeCurrent(data.window, data.ctx);

	struct SapphireSG_Context *const ctx = SG_CreateContext(SG_OpenGL, 2, 0);

	glClearColor(0, 0, 0, 0xFF);

	{

		struct SapphireSG_Group *const group = SG_CreateGroup(ctx);
		struct SapphireSG_Shape *const shape = SG_CreateShape(ctx);
		SDL_Event e;
		do {
			SDL_WaitEventTimeout(&e, 16);

		} while (e.type != SDL_QUIT);


	}

}
