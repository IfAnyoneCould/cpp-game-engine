#include "GameObject.h"

void GameObject::setPosition(const Vector2& pos) const {
    body->setPosition(pos);
    shape->setOffset(pos);
    if (animation) animation->setOffset(pos);
}

void GameObject::setPhysicsVelocity(const Vector2 &vel) const {
    body->setPhysicsVelocity(vel);
}

void GameObject::applyForces(double deltaTime) const {
    body->applyForces(deltaTime);
}

void GameObject::updateControllers(double deltaTime) const {
    for (const auto& c : controllers) {
        c->update(deltaTime);
        if (c->overridesVelocity()) {
            body->setControllerVelocity(c->getVelocity());
        } else {
            body->addControllerVelocity(c->getVelocity());
        }
    }
}

void GameObject::applyVelocity(double deltaTime) const {
    body->applyVelocity(deltaTime);
    shape->setOffset(body->getPosition());
    //body->setOnGround(false);
}

void GameObject::addPhysicsVelocity(const Vector2& vel) const {
    body->addPhysicsVelocity(vel);
}
