#include "TopDownController.h"
#include "../Vectors.h"
#include <SDl2/SDL.h>

void TopDownController::update(double deltaTime) {
    velocity = Vectors::ZERO;
    if (keys[SDL_SCANCODE_LEFT] || keys[SDL_SCANCODE_A]) velocity += Vectors::LEFT;
    if (keys[SDL_SCANCODE_RIGHT] || keys[SDL_SCANCODE_D]) velocity += Vectors::RIGHT;
    if (keys[SDL_SCANCODE_UP] || keys[SDL_SCANCODE_W]) velocity += Vectors::UP;
    if (keys[SDL_SCANCODE_DOWN] || keys[SDL_SCANCODE_S]) velocity += Vectors::DOWN;
    velocity = velocity.normalized();
    velocity *= maxSpeed;
}
