#pragma once

struct Color {
    float r, g, b;
    constexpr Color(float r, float g, float b) : r(r), g(g), b(b) {}
};

namespace Colors {
    inline constexpr Color RED = {1.0f, 0.0f, 0.0f};
    inline constexpr Color GREEN = {0.0f, 1.0f, 0.0f};
    inline constexpr Color BLUE = {0.0f, 0.0f, 1.0f};
    inline constexpr Color BLACK = {0.0f, 0.0f, 0.0f};
    inline constexpr Color WHITE = {1.0f, 1.0f, 1.0f};
}