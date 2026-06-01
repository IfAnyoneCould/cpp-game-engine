#include "Engine.h"

namespace Engine {

    static SDL_Window* window;
    static SDL_GLContext ctx;

    static const Uint8* keys;
    static SDL_Event event;

    static bool running = true;

    //timing
    static Uint64 now = SDL_GetPerformanceCounter();
    static Uint64 last = 0;
    static double deltaTime = 0;

    void init() {

        // init sdl
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            std::cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
            return;
        }

        // setup sdl for opengl
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION,3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION,3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

        //create the window and rendering variables
        window = SDL_CreateWindow("Physics",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,Constants::WORLD_WIDTH,Constants::WORLD_HEIGHT,SDL_WINDOW_OPENGL);
        SDL_GLContext ctx = SDL_GL_CreateContext(window);

        //tell opengl where its functions are (blind mf)
        gladLoadGLLoader(SDL_GL_GetProcAddress);

        SDL_PumpEvents();

        keys = SDL_GetKeyboardState(NULL);
        SDL_Event event;

    }

    void startFrame() {
        last = now;
        now = SDL_GetPerformanceCounter();
        deltaTime = static_cast<double>(now - last) / SDL_GetPerformanceFrequency();

        SDL_PumpEvents();

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

    }

    void endFrame() {
        SDL_GL_SwapWindow(window);
    }

    void quit() {
        SDL_GL_DeleteContext(ctx);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }


    //getters
    double getDeltaTime() {return deltaTime;}
    const Uint8 *getKeys() {return keys;}
    SDL_Event getEvents() {return event;}
    bool isRunning() {return running;}
}
