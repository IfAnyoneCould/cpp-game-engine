#pragma once
#include "Vector2.h"

namespace Geometry {
    inline bool linesIntersect(const Vector2& a, const Vector2& b, const Vector2& c, const Vector2& d) {
        float oa = Vector2::orient(c,d,a),
         ob = Vector2::orient(c,d,b),
         oc = Vector2::orient(a,b,c),
         od = Vector2::orient(a,b,d);

        return (oa*ob < 0 && oc*od < 0);
    }

    inline float getOverlap(float a1, float a2, float b1, float b2) {
        return std::min(a2, b2) - std::max(a1, b1);
    }
}