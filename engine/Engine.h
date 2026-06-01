#pragma once

#include <SDL2/SDL.h>
#include<glad/glad.h>
#include <iostream>
#include <utility>
#include "Shader.h"
#include "RegularPolygon.h"
#include "MovementController.h"
#include "Rectangle.h"
#include "GameObject.h"
#include "Physics.h"

namespace Engine {

    void init();
    void update(double deltaTime);
    void startFrame();
    void endFrame();
    void quit();

    //getters
    double getDeltaTime();
    const Uint8* getKeys();
    SDL_Event getEvents();
    bool isRunning();

}
