#include "GameObject.h"

void GameObject::setPosition(const Vector2& pos) const {
    body->setPosition(pos);
}

void GameObject::setVelocity(const Vector2 &vel) const {
    body->setVelocity(vel);
}

void GameObject::update(double deltaTime) const {
    body->update(deltaTime);
    shape->setOffset(body->getPosition());
}
