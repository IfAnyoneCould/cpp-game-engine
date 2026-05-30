#pragma once
#include "Vector2.h"
#include "Geometry.h"

class Triangle {
    Vector2 a,b,c;

public:
    Triangle(const Vector2& a, const Vector2& b, const Vector2& c) {this->a = a; this->b =b; this->c = c;};

    // getters
    const Vector2& getA() const {return a;}
    const Vector2& getB() const {return b;}
    const Vector2& getC() const {return c;}

    [[nodiscard]] Vector2 centroid() const {return (a + b + c) / 3;}
    float area() const {return std::abs((b-a).cross(c-a)) / 2;}
    float perimeter() const {return a.distanceTo(b) + b.distanceTo(c) + c.distanceTo(a);}
    Triangle translated(const Vector2& v) const { return {a + v, b + v, c + v};}
    bool contains(const Vector2& p) const {
        float d1 = Vector2::orient(a,b,p),
              d2 = Vector2::orient(b,c,p),
              d3 = Vector2::orient(c,a,p);

        bool neg = (d1 < 0) || (d2 < 0) || (d3 < 0);
        bool pos = (d1 > 0) || (d2 > 0) || (d3 > 0);

        return !(neg && pos);
    }
    bool intersects(const Triangle& t) const {
        if (contains(t.a) || contains(t.b) || contains(t.c)) return true;
        if (t.contains(a) || t.contains(b) || t.contains(c)) return true;

        Vector2 set1[3][2] = {{a,b},{b,c},{c,a}};
        Vector2 set2[3][2] = {{t.a,t.b},{t.b,t.c},{t.c,t.a}};
        for (const auto& i : set1) {
            for (const auto& j : set2) {
                if (Geometry::linesIntersect(i[0],i[1],j[0],j[1])) {return true;};
            }
        }
        return false;
    };
};