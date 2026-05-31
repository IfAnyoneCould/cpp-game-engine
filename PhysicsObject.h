#pragma once
#include <vector>
#include "Vector2.h"

class PhysicsObject {
    Vector2 pos = Vector2{};
    Vector2 velocity = Vector2{};

    float mass = 1;

    Vector2 netForce = Vector2{};

public:
    explicit PhysicsObject(float mass) {this->mass = mass;};

    void setForces(const std::vector<Vector2>& forces);
    void addForce(const Vector2& force) {netForce+=force;}
    void removeForce(const Vector2& force) {netForce-=force;}

    // main functions
    void update(double deltaTime);

    //get and set
    float getMass() const {return mass;};
    Vector2 getPosition() const {return pos;}
    Vector2 getVelocity() const {return velocity;}
    Vector2 getNetForce() const {return netForce;}
    void setPosition(const Vector2& other) {pos = other;}
    void setVelocity(const Vector2& other) { velocity = other;}
    void addVelocity(const Vector2& other) { velocity += other;}
};
