#include "MovementController.h"
#include "Vectors.h"
#include <SDl2/SDL.h>

void MovementController::update(double deltaTime) {
    velocity = Vectors::ZERO;
    if (keys[SDL_SCANCODE_LEFT]) velocity += Vectors::LEFT;
    if (keys[SDL_SCANCODE_RIGHT]) velocity += Vectors::RIGHT;
    if (keys[SDL_SCANCODE_UP]) velocity += Vectors::UP;
    if (keys[SDL_SCANCODE_DOWN]) velocity += Vectors::DOWN;
    velocity = velocity.normalized();
    velocity *= MAX_SPEED;
}
