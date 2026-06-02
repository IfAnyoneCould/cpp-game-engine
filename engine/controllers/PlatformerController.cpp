#include "PlatformerController.h"
#include <SDL2/SDL.h>
#include "../Vectors.h"

void PlatformerController::update(double deltaTime) {
    velocity.x = 0.0f;
    if (keys[SDL_SCANCODE_LEFT] || keys[SDL_SCANCODE_A]) velocity.x = -maxSideSpeed;
    if (keys[SDL_SCANCODE_RIGHT] || keys[SDL_SCANCODE_D]) velocity.x = maxSideSpeed;

    if (body->isOnGround() && (keys[SDL_SCANCODE_UP] || keys[SDL_SCANCODE_W])) {
        velocity.y = upwardForce;
    };

    velocity += Vectors::GRAVITY * deltaTime;
}
