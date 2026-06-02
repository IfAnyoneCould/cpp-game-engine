#pragma once
#include <memory>

#include "Shape.h"
#include "PhysicsObject.h"
#include "controllers/Controller.h"

class GameObject {
    Shape* shape;
    std::unique_ptr<PhysicsObject> body;
    std::vector<Controller*> controllers;

public:
    GameObject(Shape* shape, PhysicsObject* body) : shape(shape), body(body){}
    GameObject(Shape* shape, float mass) : shape(shape), body(std::make_unique<PhysicsObject>(mass)) {}
    GameObject(Shape* shape) : shape(shape), body(std::make_unique<PhysicsObject>(1)) {body->setFixed(true);body->setGravity(false);}

    void setPosition(const Vector2& pos) const;
    void setPhysicsVelocity(const Vector2& vel) const;
    void addPhysicsVelocity(const Vector2& vel) const;
    void setFixed(bool fixed) const {body->setFixed(fixed);}
    void setKinematic(bool kin) const {body->setKinematic(kin);}
    void addController(Controller* controller) {controller->setBody(body.get());controllers.push_back(controller);};

    Shape& getShape() const {return *shape;}
    PhysicsObject& getBody() const {return *body;}
    Vector2 getTotalVelocity() const {return body->getVelocity();}
    Vector2 getPhysicsVelocity() const {return body->getPhysicsVelocity();}
    Vector2 getControllerVelocity() const {return body->getControllerVelocity();}
    Vector2 getPosition() const {return body->getPosition();}
    bool isFixed() const {return body->isFixed();}
    bool isKinematic() const {return body->isKinematic();}

    void applyForces(double deltaTime) const;
    void applyVelocity(double deltaTime) const;
    void updateControllers(double deltaTime) const;


};