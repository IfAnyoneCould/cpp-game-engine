#pragma once
#include "GameObject.h"

namespace Physics {
    Collision collision(GameObject& a, GameObject& b);
    Collision collision(GameObject& a, GameObject& b, Collision collision);
    Vector2 cancelAlongNormal(Vector2 velocity, Collision collision);
}