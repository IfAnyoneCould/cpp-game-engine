#pragma once
#include <SDL_stdinc.h>

#include "Controller.h"

class PlatformerController : public Controller {
    float maxSideSpeed;
    float upwardForce;
    const Uint8* keys;

public:
    PlatformerController(float max, float force, const Uint8* keys) : Controller(true), maxSideSpeed(max), upwardForce(force), keys(keys) {}

    void update(double deltaTime) override;

};