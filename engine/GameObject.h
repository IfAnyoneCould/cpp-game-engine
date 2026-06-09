#pragma once
#include <memory>
#include <utility>
#include "Shape.h"
#include "PhysicsObject.h"
#include "controllers/Controller.h"
#include "Animation.h"

class GameObject {
    std::string id;
    std::unique_ptr<Shape> shape;
    std::unique_ptr<Animation> animation;
    std::unique_ptr<PhysicsObject> body;
    std::vector<Controller*> controllers;

public:
    //there has got to be a better way to do this, for now it works
    GameObject(Shape* shape, PhysicsObject* body, std::string  name) : id(std::move(name)), shape(shape), body(body){}
    GameObject(Shape* shape, float mass, std::string name) : shape(shape), body(std::make_unique<PhysicsObject>(mass)), id(std::move(name)){}
    GameObject(Shape* shape, std::string name) : shape(shape), body(std::make_unique<PhysicsObject>(1)), id(std::move(name)) {body->setFixed(true);body->setGravity(false);}
    GameObject(Animation* anim, std::string name) : animation(anim), body(std::make_unique<PhysicsObject>(1)), id(std::move(name)) {body->setFixed(true);body->setGravity(false);}
    GameObject(Animation* anim, Shape* shape, std::string name) : id(std::move(name)), animation(anim), shape(shape), body(std::make_unique<PhysicsObject>(1)) {body->setFixed(true),body->setGravity(false);}
    GameObject(Animation* anim, Shape* shape, PhysicsObject* body, std::string name) : id(std::move(name)), animation(anim), body(body), shape(shape) {};
    GameObject(Animation* anim, Shape* shape, float mass, std::string name) : id(std::move(name)), animation(anim), shape(shape), body(std::make_unique<PhysicsObject>(mass)) {};

    void setPosition(const Vector2& pos) const;
    void setPhysicsVelocity(const Vector2& vel) const;
    void addPhysicsVelocity(const Vector2& vel) const;
    void setFixed(bool fixed) const {body->setFixed(fixed);}
    void setKinematic(bool kin) const {body->setKinematic(kin);}
    void addController(Controller* controller) {controller->setBody(body.get());controllers.push_back(controller);};
    void setID(std::string name) {id = std::move(name);}

    Shape& getShape() const {return *shape;}
    PhysicsObject& getBody() const {return *body;}
    Animation& getAnimation() const {return *animation;}
    Vector2 getTotalVelocity() const {return body->getVelocity();}
    Vector2 getPhysicsVelocity() const {return body->getPhysicsVelocity();}
    Vector2 getControllerVelocity() const {return body->getControllerVelocity();}
    Vector2 getPosition() const {return body->getPosition();}
    bool isFixed() const {return body->isFixed();}
    bool isKinematic() const {return body->isKinematic();}
    const std::string& getID() const {return id;}

    void applyForces(double deltaTime) const;
    void applyVelocity(double deltaTime) const;
    void updateControllers(double deltaTime) const;
    void draw(double deltaTime) const {animation->draw(deltaTime);}


};