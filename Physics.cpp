#include "Physics.h"
#include <iostream>

void Physics::collision(GameObject& a, GameObject& b) {
    Collision collision = a.getShape().intersectsSAT(b.getShape());

    if (collision.collided) {
        float invMassA = a.isFixed() ? 0 : 1 / a.getBody().getMass();
        float invMassB = b.isFixed() ? 0 : 1 / b.getBody().getMass();

        float restitution = 0.8f;
        Vector2 relVel = a.getVelocity() - b.getVelocity();
        float normalVel = Vector2::dot(relVel,collision.normal);

        if (normalVel > 0) return;

        float j = -(1 + restitution) * normalVel / (invMassA + invMassB);

        Vector2 impulse = collision.normal * j;

        if (!a.isFixed()) a.setVelocity(a.getVelocity() + impulse * invMassA);
        if (!b.isFixed()) b.setVelocity(b.getVelocity() - impulse * invMassB);

        /*
        const float percent = 0.2f;
        Vector2 correction = collision.normal * (collision.depth / (invMassA + invMassB)) * percent;
        if (!a.isFixed()) a.setPosition(a.getPosition() + correction * invMassA);
        if (!b.isFixed()) b.setPosition(b.getPosition() - correction * invMassB);
        */
    }

}