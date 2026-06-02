#include "GameObject.h"

void GameObject::setPosition(const Vector2& pos) const {
    body->setPosition(pos);
}

void GameObject::setVelocity(const Vector2 &vel) const {
    body->setVelocity(vel);
}

void GameObject::applyForces(double deltaTime) const {
    body->applyForces(deltaTime);
}

void GameObject::applyVelocity(double deltaTime) const {
    body->applyVelocity(deltaTime);
    shape->setOffset(body->getPosition());
}

void GameObject::addVelocity(const Vector2 vel) const {
    body->addVelocity(vel);
}
