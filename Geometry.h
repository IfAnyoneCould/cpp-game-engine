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
}