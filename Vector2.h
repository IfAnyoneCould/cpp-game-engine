#pragma once
#include <cmath>
#include "Unit.h"
#include "Constants.h"

struct Vector2 {
    float x = 0;
    float y = 0;

    //overloading operations
    Vector2& operator+=(const Vector2& other) {x += other.x; y += other.y; return *this;}
    Vector2& operator-=(const Vector2& other) {x -= other.x; y -= other.y; return *this;}
    Vector2& operator*=(float other) {x *= other; y *= other; return *this;}
    Vector2& operator/=(float other) {x /= other; y /= other; return *this;}
    bool operator==(const Vector2& other) const {return x==other.x && y==other.y;}
    bool operator!=(const Vector2& other) const {return !(*this==other);}

    Vector2 operator+(const Vector2& other) const {Vector2 r = *this; r+=other; return r;}
    Vector2 operator-(const Vector2& other) const {Vector2 r = *this; r-=other; return r;}
    Vector2 operator*(float other) const {Vector2 r = *this; r*=other; return r;}
    Vector2 operator/(float other) const {Vector2 r = *this; r/=other; return r;}

    //get operations
    float magnitude() const {return std::sqrt(x*x + y*y);}
    float magnitudeSquared() const {return x*x + y*y;}
    float directionRad() const {return std::atan2(y,x);}
    float directionDeg() const {return directionRad() * 180 / M_PI;}

    //other operations
    float dot(const Vector2& other) const {return x * other.x + y * other.y;}
    float cross(const Vector2& other) const { return x * other.y - y * other.x; }
    Vector2 normalized() const {float m = magnitude(); return m > 0 ? *this / m : Vector2{};}
    Vector2 pixelEquivalent() const {return Vector2(Unit::unitToPixel(x),Unit::unitToPixel(y));}
    Vector2 unitEquivalent() const {return Vector2(Unit::pixelToUnit(x),Unit::pixelToUnit(y));}
    static Vector2 fromRadiansAndMagnitude(float angle, float magnitude) {return {magnitude * cosf(angle), magnitude * sinf(angle)};}
    static Vector2 fromDegreesAndMagnitude(float angle, float magnitude) {return {magnitude * cosf(angle * Constants::PI / 180.0f), magnitude * sinf(angle * Constants::PI / 180.0f)};}
    float distanceTo(const Vector2& other) const {return (*this-other).magnitude();}
    float distanceToSquared(const Vector2& other) const {return (*this-other).magnitudeSquared();}

};
