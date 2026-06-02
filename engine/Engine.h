#pragma once

#include <SDL2/SDL.h>
#include<glad/glad.h>
#include <iostream>
#include <utility>
#include "Shader.h"
#include "RegularPolygon.h"
#include "controllers/TopDownController.h"
#include "controllers/PlatformerController.h"
#include "Rectangle.h"
#include "GameObject.h"
#include "Physics.h"
#include "Camera.h"

namespace Engine {

    void init();
    void startFrame();
    void endFrame();
    void quit();

    //getters
    double getDeltaTime();
    const Uint8* getKeys();
    SDL_Event getEvents();
    bool isRunning();
    unsigned int getProgram();

}
