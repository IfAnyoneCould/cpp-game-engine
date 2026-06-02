#include "Mat4.h"
#include <iostream>

Mat4 Mat4::identity() {
    float result[16] ={};

    for (int i = 0; i < 16; i+=5) {
        result[i] = 1.0f;
    }
    return {result};
}

Mat4 Mat4::operator*(const Mat4 &other) const {
    Mat4 result;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            result.m[i + j * 4] = 0;
            for (int k = 0; k < 4; k++) {
                result.m[i + j * 4] += m[i + k * 4] * other.m[k + j * 4];
            }
        }
    }
    return result;
}

Mat4 Mat4::scale(const Vector2 &vec) {
    Mat4 result;
    result.m[0] = vec.x;
    result.m[5] = vec.y;
    result.m[10] = 1.0f;
    result.m[15] = 1.0f;
    return result;
}

Mat4 Mat4::translate(const Vector2 &vec) {
    Mat4 result = identity();
    result.m[12] = vec.x;
    result.m[13] = vec.y;
    return result;
}

Mat4 Mat4::rotateDegrees(float theta) {
    float radians = theta / 180 * Constants::PI;
    return rotateRadians(radians);
}

Mat4 Mat4::rotateRadians(float theta) {
    Mat4 result = identity();
    result.m[0] = cosf(theta);
    result.m[4] = -sinf(theta);
    result.m[1] = sinf(theta);
    result.m[5] = cosf(theta);
    return result;
}

Mat4 Mat4::orthographic(float left, float right, float bottom, float top) {
    Mat4 result;
    result.m[0]  = 2.0f / (right - left);
    result.m[5]  = 2.0f / (top - bottom);
    result.m[10] = -1.0f;
    result.m[12] = -(right + left) / (right - left);
    result.m[13] = -(top + bottom) / (top - bottom);
    result.m[15] = 1.0f;
    return result;
}
