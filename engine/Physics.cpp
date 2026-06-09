#include "Physics.h"
#include <iostream>

void Physics::collision(GameObject& a, GameObject& b, Collision collision) {
    if (collision.collided) {
        float invMassA = a.isFixed() ? 0 : a.getBody().getInvMass();
        float invMassB = b.isFixed() ? 0 : b.getBody().getInvMass();

        float restitution = 0.8f;
        Vector2 relVel = a.getTotalVelocity() - b.getTotalVelocity();
        float normalVel = Vector2::dot(relVel,collision.normal);

        if (normalVel > 0) return;

        float j = -(1 + restitution) * normalVel / (invMassA + invMassB);

        Vector2 impulse = collision.normal * j;

        if (!a.isFixed() && !a.isKinematic()) a.setPhysicsVelocity(a.getPhysicsVelocity() + impulse * invMassA);
        if (!b.isFixed() && !b.isKinematic()) b.setPhysicsVelocity(b.getPhysicsVelocity() - impulse * invMassB);

        if (a.isKinematic()) {
            a.getBody().setPhysicsVelocity(cancelAlongNormal(a.getPhysicsVelocity(),collision));
            a.getBody().setControllerVelocity(cancelAlongNormal(a.getControllerVelocity(),collision));
        }
        if (b.isKinematic()) {
            b.getBody().setPhysicsVelocity(cancelAlongNormal(b.getPhysicsVelocity(),collision));
            b.getBody().setControllerVelocity(cancelAlongNormal(b.getControllerVelocity(),collision));
        }

        const float percent = 0.2f;
        Vector2 correction = collision.normal * (collision.depth / (invMassA + invMassB)) * percent;
        if (!a.isFixed()) a.setPosition(a.getPosition() + correction * invMassA);
        if (!b.isFixed()) b.setPosition(b.getPosition() - correction * invMassB);
    }

}

Collision Physics::collision(GameObject &a, GameObject &b) {
    Collision collision = a.getShape().intersectsSAT(b.getShape());

    if (collision.collided) {
        //std::cout << collision.normal.y << std::endl;
        if (collision.normal.y > 0) a.getBody().setOnGround(true);
        if (collision.normal.y < 0) b.getBody().setOnGround(true);
    }
    return collision;
}


Vector2 Physics::cancelAlongNormal(Vector2 velocity, Collision collision) {
    float alongNormalPhysics = Vector2::dot(velocity,collision.normal);
    if (alongNormalPhysics < 0) {
        return velocity - collision.normal * alongNormalPhysics;
    }
    return velocity;
}
