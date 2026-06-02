#include "PhysicsObject.h"
#include "Vectors.h"

void PhysicsObject::applyForces(double deltaTime) {
    velocity+=netForce * invMass * deltaTime;
    netForce = Vectors::ZERO;
}

void PhysicsObject::applyVelocity(double deltaTime) {
    pos+=velocity * deltaTime;
}

void PhysicsObject::setForces(const std::vector<Vector2>& otherForces) {
    this->netForce = Vectors::ZERO;
    for (const auto& f : otherForces) {
        netForce += f;
    }
}
