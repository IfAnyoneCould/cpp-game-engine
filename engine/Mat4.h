#pragma once
#include <cstring>
#include "Vector2.h"

class Mat4 {
    float m[16];

public:
    Mat4() {std::fill(m ,m + 16,0.0f);};
    Mat4(float n[16]) {std::memcpy(m,n,sizeof(m));};

    const float* getM() const {return m;}

    static Mat4 scale(const Vector2& vec);
    static Mat4 rotateRadians(float theta);
    static Mat4 rotateDegrees(float theta);
    static Mat4 translate(const Vector2& vec);
    static Mat4 identity();
    static Mat4 orthographic(float left, float right, float bottom, float top);

    Mat4 operator*(const Mat4& other) const;

};