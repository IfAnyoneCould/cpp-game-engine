#include "Rectangle.h"

Rectangle::Rectangle(float width, float height, const Shader& program)
    : Shape([&]() {
        std::vector<Triangle> tri;
        tri.push_back({{0,0},{width,0},{width,height}});
        tri.push_back({{0,0},{0,height},{width,height}});
        return tri;
    }(),program), height(height), width(width) {genBuffer();}

Rectangle::Rectangle(float width, float height, const Color& color, const Shader& program)
    :   Rectangle(width,height,program){
    this->color = color;
}

Vector2 Rectangle::localCenter() const {
    return {width/2,height/2};
}

bool Rectangle::contains(const Vector2 &other) const {
    const Vector2 check = other-offset;
    return ( 0 <= check.x && check.x <= width) && (0 <= check.y && check.y <= height);
}
