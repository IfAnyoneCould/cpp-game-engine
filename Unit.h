#pragma once

namespace Unit {
    constexpr float PIXEL_PER_UNIT = 10.0f;

    constexpr float unitToPixel(float unit) {
        return unit * PIXEL_PER_UNIT;
    }
    constexpr float pixelToUnit(float pixels) {
        return pixels / PIXEL_PER_UNIT;
    }
}