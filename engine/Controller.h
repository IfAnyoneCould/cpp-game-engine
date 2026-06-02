#pragma once
#include "Vector2.h"

class Controller {
protected:
    Vector2 velocity;
    bool overrideVel;

public:
    virtual ~Controller() = default;

    explicit Controller(bool over) : overrideVel(over) {};

    virtual void update(double deltaTime) = 0;
    virtual Vector2 getVelocity() const {return velocity;};
    virtual bool overridesVelocity() const {return overrideVel;}

};