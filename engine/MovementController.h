#pragma once
#include <SDL_stdinc.h>
#include "Vector2.h"
#include "Controller.h"

class MovementController : public Controller{
    float MAX_SPEED;
    const Uint8* keys;

public:
    explicit MovementController(float max, const Uint8* keys) : MAX_SPEED(max), keys(keys), Controller(true) {}

    void update(double deltaTime) override;

};