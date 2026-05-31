#pragma once
#include "Shape.h"
#include "PhysicsObject.h"

class GameObject {
    Shape* shape;
    PhysicsObject* body;

public:
    GameObject(Shape* shape, PhysicsObject* body) : shape(shape), body(body){}

    void setPosition(const Vector2& pos) const;
    void setVelocity(const Vector2& vel) const;

    Shape& getShape() const {return *shape;}
    PhysicsObject& getBody() const {return *body;}
    Vector2 getVelocity() const {return body->getVelocity();}
    Vector2 getPosition() const {return body->getPosition();}

};