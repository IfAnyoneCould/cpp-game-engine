#pragma once
#include <vector>
#include "Vector2.h"

class PhysicsObject {
    Vector2 pos = Vector2{};
    Vector2 velocity = Vector2{};
    bool fixed = false;
    bool kinematic = false;

    float mass = 1;
    float invMass;

    Vector2 netForce = Vector2{};

public:
    explicit PhysicsObject(float mass) {this->mass = mass;this->invMass = 1/ mass;};

    void setForces(const std::vector<Vector2>& forces);
    void addForce(const Vector2& force) {netForce+=force;}
    void removeForce(const Vector2& force) {netForce-=force;}

    // main functions
    //void update(double deltaTime);
    void applyForces(double deltaTime);
    void applyVelocity(double deltaTime);


    //get and set
    float getMass() const {return mass;};
    float getInvMass() const {return invMass;}
    Vector2 getPosition() const {return pos;}
    Vector2 getVelocity() const {return velocity;}
    Vector2 getNetForce() const {return netForce;}
    bool isFixed() const {return fixed;}
    bool isKinematic() const {return kinematic;}
    void setPosition(const Vector2& other) {pos = other;}
    void setVelocity(const Vector2& other) { velocity = other;}
    void addVelocity(const Vector2& other) { velocity += other;}
    void setFixed(bool fix) {fixed = fix;}
    void setKinematic(bool kin) {kinematic = kin;}
};
