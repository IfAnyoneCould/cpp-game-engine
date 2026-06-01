#pragma once
#include <memory>

#include "Shape.h"
#include "PhysicsObject.h"

class GameObject {
    Shape* shape;
    std::unique_ptr<PhysicsObject> body;

public:
    GameObject(Shape* shape, PhysicsObject* body) : shape(shape), body(body){}
    GameObject(Shape* shape, float mass) : shape(shape), body(std::make_unique<PhysicsObject>(mass)) {}
    GameObject(Shape* shape) : shape(shape), body(std::make_unique<PhysicsObject>(1)) {body->setFixed(true);}

    void setPosition(const Vector2& pos) const;
    void setVelocity(const Vector2& vel) const;
    void setFixed(bool fixed) const {body->setFixed(fixed);}

    Shape& getShape() const {return *shape;}
    PhysicsObject& getBody() const {return *body;}
    Vector2 getVelocity() const {return body->getVelocity();}
    Vector2 getPosition() const {return body->getPosition();}
    bool isFixed() const {return body->isFixed();}

    void update(double deltaTime) const;

};