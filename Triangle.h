#pragma once
#include "Vector2.h"

class Triangle {
    Vector2 a,b,c;

public:
    Triangle(const Vector2& a, const Vector2& b, const Vector2& c) {this->a = a; this->b =b; this->c = c;};

    // getters
    const Vector2& getA() const {return a;}
    const Vector2& getB() const {return b;}
    const Vector2& getC() const {return c;}

    Vector2 centroid() const {return (a + b + c) / 3;}
    float area() const {return std::abs((b-a).cross(c-a)) / 2;}
    float perimeter() const {return a.distanceTo(b) + b.distanceTo(c) + c.distanceTo(a);}
    bool contains(const Vector2&);

};