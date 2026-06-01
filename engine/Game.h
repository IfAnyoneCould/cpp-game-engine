#pragma once
#include "Engine.h"

void start();
void update(double deltaTime);

#define RUN \
    int main(int arc, char* argv[]) {\
        Engine::init();\
        start(); \
        while(Engine::isRunning()) { \
            Engine::startFrame(); \
            update(Engine::getDeltaTime()); \
            Engine::endFrame(); \
        }   \
        Engine::quit(); \
        return 0; \
    }

