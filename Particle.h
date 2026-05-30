#pragma once
#include <SDL_render.h>
#include <vector>
#include "Vector2.h"

class Particle {
    Vector2 pos = Vector2{};
    Vector2 velocity = Vector2{};

    float mass = 1;

    std::vector<Vector2> forces;
    Vector2 netForce = Vector2{};

public:
    explicit Particle(Vector2 pos);

    void setForces(const std::vector<Vector2>& forces);
    void addForce(const Vector2& force) {forces.push_back(force); netForce+=force;}
    void removeForce(int index) {netForce-=forces[index]; forces.erase(forces.begin() + index);}
    void calcNetForce() {netForce = Vector2{}; for (const auto& f : forces) {netForce += f;}}


    // main functions
    void update(double deltaTime);
    void draw(SDL_Renderer* renderer) const;

    //get and set
    float getMass() const {return mass;};
    const Vector2& getPosition() const {return pos;}
    const Vector2& getVelocity() const {return velocity;}
    const Vector2& getNetForce() const {return netForce;}
    void setPosition(const Vector2& other) {pos = other;}
    void setVelocity(const Vector2& other) { velocity = other;}
    void addVelocity(const Vector2& other) { velocity += other;}
};
