#include "sapphire.hpp"
#include "SDL2/SDL.h"
#include <cstdio>
#include <cstdlib>

int main(int argc, char *argv[]){
    if(argc || argv){} // Silence Clang warnings
    
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
    // Create a window
    SDL_Window *const window = SDL_CreateWindow("Sapphire", 
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480,
        SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI);
    
    // Setup OpenGL attribs
    SDL_GL_ResetAttributes();
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);

    
    // Create OpenGL context
    SDL_GLContext gl_ctx = SDL_GL_CreateContext(window);
    SDL_GL_MakeCurrent(window, gl_ctx);
    
    // Create Sapphire context
    Sapphire::Context *const ctx = Sapphire::Context::Create(Sapphire::Context::eOpenGL2);
    if(!ctx){
        fputs("Could not create context\n", stderr);
        return EXIT_FAILURE;
    }
    // Setup view
    Sapphire::ShaderProgram *const program = ctx->createShaderProgram();
    program->setDiffuseLight(1.0f, 1.0f, 1.0f);
    program->setFrustum(-1.0f, 1.0f, 1.0f, -1.0f, 0.01f, 1000.0f);
    
    // Upload a shape
    Sapphire::VertexF triangle_vertices1[3], triangle_vertices2[3];
    triangle_vertices1[0].xyz(0.0f, -0.5f, 1.0f);
    triangle_vertices1[1].xyz(0.5f, 0.5f, 1.0f);
    triangle_vertices1[2].xyz(-0.5f, -0.5f, 1.0f);

    triangle_vertices2[0].xyz(-0.5f, -0.5f, 1.0f);
    triangle_vertices2[1].xyz(0.5f, 0.5f, 1.0f);
    triangle_vertices2[2].xyz(0.0f, -0.5f, 1.0f);
    
    // All white for color.
    unsigned white = 0xFFFFFFFF;
    Sapphire::Image *const white_image = ctx->createImage(&white, 1, 1);
    Sapphire::Shape *shapes[2] = {
        ctx->createShape(triangle_vertices1, 3),
        ctx->createShape(triangle_vertices2, 3)
    };
    
    shapes[0]->image(white_image);
    shapes[1]->image(white_image);
    
    Sapphire::Group *const group = ctx->createGroup(shapes, 2);
    group->program(program);
    
    // Draw 'til you die
    SDL_Event e;
    do{
        // Run about 60 FPS
        SDL_WaitEventTimeout(&e, 16);
        
        // Draw group
        group->draw();
        
        // Flip and clear
        SDL_GL_SwapWindow(window);
        ctx->clearScreen();
    }while(e.type != SDL_QUIT);
    
    return EXIT_SUCCESS;
}

extern "C"
int WinMain(int argc, char *argv[]){
    return main(argc, argv);
}
