#pragma once
#include <SDL_stdinc.h>
#include "Vector2.h"

class MovementController {
    Vector2 pos = Vector2{};
    Vector2 velocity = Vector2{};
    float MAX_SPEED;

public:
    explicit MovementController(float max) {this->MAX_SPEED = max;}

    [[nodiscard]] const Vector2& getPosition() const {return pos;}
    [[nodiscard]] const Vector2& getVelocity() const {return velocity;}

    void update(double deltaTime,const Uint8* keys);

};