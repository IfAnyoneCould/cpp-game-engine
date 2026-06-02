#pragma once
#include "Shape.h"

class Rectangle : public Shape {
    float height;
    float width;

public:

    Rectangle(float width, float height, const Shader& program);
    Rectangle(float width, float height, const Color& color, const Shader& program);

    [[nodiscard]] float getWidth() const {return width;}
    [[nodiscard]] float getHeight() const {return height;}
    [[nodiscard]] Vector2 localCenter() const override;
    [[nodiscard]] bool contains(const Vector2& other) const override;

};