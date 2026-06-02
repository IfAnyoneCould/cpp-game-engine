#pragma once
#include <SDL_stdinc.h>
#include "../Vector2.h"
#include "Controller.h"

class TopDownController : public Controller{
    float maxSpeed;
    const Uint8* keys;

public:
    explicit TopDownController(float max, const Uint8* keys) : maxSpeed(max), keys(keys), Controller(true) {}

    void update(double deltaTime) override;

};