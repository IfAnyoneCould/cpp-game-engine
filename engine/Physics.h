#pragma once
#include "GameObject.h"

namespace Physics {
    void collision(GameObject&, GameObject&);
    Vector2 cancelAlongNormal(Vector2 velocity, Collision collision);
}