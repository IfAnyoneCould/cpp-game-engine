#pragma once
#include "Engine.h"

void start();
void update(double deltaTime);
void render();

#define RUN \
    int main(int arc, char* argv[]) {\
        Engine::init();\
        start(); \
        constexpr double PHYSICS_STEP = 1.0 / 240.0; \
        double accumulator = 0; \
        while(Engine::isRunning()) { \
            Engine::startFrame(); \
            accumulator += Engine::getDeltaTime(); \
            while (accumulator >= PHYSICS_STEP) { \
            update(PHYSICS_STEP); \
            accumulator -= PHYSICS_STEP; \
            } \
            render(); \
            Engine::endFrame(); \
        }   \
        Engine::quit(); \
        return 0; \
    }

