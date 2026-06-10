#pragma once
#include "GameObject.h"

namespace Physics {
    Collision collisionSAT(GameObject& a, GameObject& b);
    Collision collisionAABB(GameObject& a, GameObject& b);
    void collision(GameObject& a, GameObject& b, Collision collision);
    Vector2 cancelAlongNormal(Vector2 velocity, Collision collision);
}