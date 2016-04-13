#include "../../src/sapphire_sg.h"
#include <assert.h>

#ifdef _WIN32
#include "SDL2/SDL.h"
#include <Windows.h>
#else
#include <SDL2/SDL.h>
#endif

#include <GL/gl.h>

static void SetSDL2OpenGLAttribs() {

	SDL_GL_ResetAttributes();

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);

/*	SDL_GL_SetAttribute(SDL_GL_SHARE_WITH_CURRENT_CONTEXT, 1);
*/
}

int main(int argc, char *argv[]) {
	SDL_Window *window;
	SDL_GLContext gl_ctx;
	struct SapphireSG_Context *sg_ctx;

	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);

	SetSDL2OpenGLAttribs();

	window = SDL_CreateWindow("SDL2 GL SapphireSG example", 32, 32, 800, 600,
		SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_MOUSE_FOCUS);

	SetSDL2OpenGLAttribs();
	gl_ctx = SDL_GL_CreateContext(window);
	SDL_GL_MakeCurrent(window, gl_ctx);

	sg_ctx = SG_CreateContext(SG_OpenGL, 2, 0);

	glClearColor(0, 0, 0, 0xFF);

	glViewport(0, 0, 800, 600);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 800, 600, 0, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	{

		struct SapphireSG_Group *const group = SG_CreateGroup(sg_ctx);
		struct SapphireSG_Shape *const shape = SG_CreateShape(sg_ctx);
		struct SapphireSG_Image *const image = SG_CreateWhiteImage(sg_ctx);

		unsigned char white[4] = { 0xFF, 0xFF, 0xFF, 0xFF };

		assert(group);
		assert(shape);
		assert(image);

		SG_SetShapeVertexCapacity(sg_ctx, shape, 3);

		SG_SetShapeVertexPosition(sg_ctx, shape, 0, 200.0, 200.0, 1.0);
		SG_SetShapeVertexPosition(sg_ctx, shape, 1, 400.0, 100.0, 1.0);
		SG_SetShapeVertexPosition(sg_ctx, shape, 2, 200.0, 300.0, 1.0);

		SG_SetShapeVertexTexturePosition(sg_ctx, shape, 0, 0.0, 0.0);
		SG_SetShapeVertexTexturePosition(sg_ctx, shape, 1, 1.0, 0.0);
		SG_SetShapeVertexTexturePosition(sg_ctx, shape, 2, 0.0, 1.0);

		SG_SetShapeVertexColorV(sg_ctx, shape, 0, white);
		SG_SetShapeVertexColorV(sg_ctx, shape, 1, white);
		SG_SetShapeVertexColorV(sg_ctx, shape, 2, white);

		SG_SetShapeImage(sg_ctx, shape, image);

		SG_SetGroupShapeCapacity(sg_ctx, group, 1);
		SG_SetGroupShape(sg_ctx, group, 0, shape);

		SDL_Event e;

		SDL_ShowWindow(window);

		glEnable(GL_TEXTURE_2D);
		glEnable(GL_CULL_FACE);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glClear(GL_COLOR_BUFFER_BIT);
		do {

			SDL_WaitEventTimeout(&e, 16);

			SG_DrawGroup(sg_ctx, group); 

			SDL_GL_SwapWindow(window);
		} while (e.type != SDL_QUIT);


	}
	return EXIT_SUCCESS;
}
