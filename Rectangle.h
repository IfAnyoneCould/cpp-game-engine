#pragma once
#include "Shape.h"

class Rectangle : public Shape {
    float height;
    float width;

public:

    Rectangle(float width, float height, unsigned int program);
    Rectangle(float width, float height, const Color& color, unsigned int program);

    [[nodiscard]] float getWidth() const {return width;}
    [[nodiscard]] float getHeight() const {return height;}
    [[nodiscard]] Vector2 localCenter() const override;

};