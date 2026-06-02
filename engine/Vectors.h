#pragma once
#include "Vector2.h"
#include "Constants.h"

namespace Vectors {
    inline constexpr Vector2 LEFT = {-1,0};
    inline constexpr Vector2 RIGHT = {1,0};
    inline constexpr Vector2 UP = {0,1};
    inline constexpr Vector2 DOWN = {0,-1};
    inline constexpr Vector2 ZERO = {};
    inline constexpr Vector2 WORLD_CENTER = {Constants::WORLD_WIDTH/2,Constants::WORLD_HEIGHT/2};
    inline constexpr Vector2 GRAVITY = {0.0f,-500.0f};
}