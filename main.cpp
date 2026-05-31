#include <SDL2/SDL.h>
#include<glad/glad.h>
#include <iostream>
#include "Shader.h"
#include "RegularPolygon.h"
#include "MovementController.h"
#include "Rectangle.h"
#include "GameObject.h"

int main(int argc, char* argv[]) {

    // init sdl
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    // setup sdl for opengl
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION,3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION,3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    //create the window and rendering variables
    SDL_Window* window = SDL_CreateWindow("Physics",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,Constants::WORLD_WIDTH,Constants::WORLD_HEIGHT,SDL_WINDOW_OPENGL);
    SDL_GLContext ctx = SDL_GL_CreateContext(window);

    //tell opengl where its functions are (blind mf)
    gladLoadGLLoader(SDL_GL_GetProcAddress);

    //init stuff here
    // -----------------------------------------------------------------------------

    unsigned int program = Shader::getProgram({
        {"shaders/vertex.glsl",GL_VERTEX_SHADER},
        {"shaders/fragment.glsl",GL_FRAGMENT_SHADER}});


    RegularPolygon shape(200.0f,6,Colors::BLUE,program);
    MovementController controller{500};
    Rectangle rect(100,500,program);

    // -----------------------------------------------------------------------------
    // sdl input stuff
    const Uint8* keys = SDL_GetKeyboardState(NULL);
    SDL_Event event;

    //time stuff
    Uint64 now = SDL_GetPerformanceCounter();
    Uint64 last = 0;
    double deltaTime = 0;

    bool running = true;
    while (running) {
        // time stuff
        last = now;
        now = SDL_GetPerformanceCounter();
        deltaTime = static_cast<double>(now - last) / SDL_GetPerformanceFrequency();

        // handles exiting
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    running = false;
                    break;
                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_ESCAPE) {
                        running = false;
                        break;
                    }
            }
        }

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //do stuff here
        //-----------------------------------------------------------------------------

        controller.update(deltaTime,keys);
        shape.setOffset(controller.getPosition());

        if (rect.intersects(shape)) {
            shape.setColor(Colors::GREEN);
        } else {
            shape.setColor(Colors::BLUE);
        }

        rect.drawWireFrame();
        shape.draw();

        //-----------------------------------------------------------------------------
        SDL_GL_SwapWindow(window);
    }

    SDL_GL_DeleteContext(ctx);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}