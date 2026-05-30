#include "Particle.h"
#include <SDL2/SDL.h>

Particle::Particle(Vector2 pos) {
    this->pos = pos;
}

void Particle::update(double deltaTime) {
        velocity += netForce / mass;
        pos += velocity * deltaTime;
}

void Particle::setForces(const std::vector<Vector2>& otherForces) {
    this->forces = otherForces;
    this->netForce = Vector2();
    for (const auto& f : forces) {
        netForce += f;
    }
}

void Particle::draw(SDL_Renderer* renderer) const {
    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    SDL_RenderDrawPoint(renderer,pos.x,pos.y);
}

