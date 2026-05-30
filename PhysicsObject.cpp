#include "PhysicsObject.h"
#include "Vectors.h"

void PhysicsObject::update(double deltaTime) {
    velocity += (netForce/mass) * deltaTime;
    pos += velocity * deltaTime;
    netForce = Vectors::ZERO;
}

void PhysicsObject::setForces(const std::vector<Vector2>& otherForces) {
    this->netForce = Vectors::ZERO;
    for (const auto& f : otherForces) {
        netForce += f;
    }
}
