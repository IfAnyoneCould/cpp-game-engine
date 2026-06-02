#pragma once
#include <vector>
#include "Vector2.h"

class PhysicsObject {
    Vector2 pos = {};
    Vector2 physicsVelocity = {};
    Vector2 controllerVelocity = {};
    bool fixed = false;
    bool kinematic = false;
    bool hasGrav = true;

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
    Vector2 getVelocity() const {return physicsVelocity + controllerVelocity;}
    Vector2 getControllerVelocity() const {return controllerVelocity;}
    Vector2 getPhysicsVelocity() const {return physicsVelocity;}
    Vector2 getNetForce() const {return netForce;}
    bool isFixed() const {return fixed;}
    bool isKinematic() const {return kinematic;}
    bool hasGravity() const {return hasGrav;}
    void setPosition(const Vector2& other) {pos = other;}
    void setPhysicsVelocity(const Vector2& other) { physicsVelocity = other;}
    void setControllerVelocity(const Vector2& other) { controllerVelocity = other;}
    void addPhysicsVelocity(const Vector2& other) { physicsVelocity += other;}
    void addControllerVelocity(const Vector2& other) { controllerVelocity += other;}
    void setFixed(bool fix) {fixed = fix;}
    void setKinematic(bool kin) {kinematic = kin;}
    void setGravity(bool grav) {hasGrav = grav;}
};
