#include "Rectangle.h"

Rectangle::Rectangle(float width, float height, unsigned int program)
    : Shape([&]() {
        std::vector<Triangle> tri;
        tri.push_back({{0,0},{width,0},{width,height}});
        tri.push_back({{0,0},{0,height},{width,height}});
        return tri;
    }(),program), height(height), width(width) {genBuffer();}

Rectangle::Rectangle(float width, float height, const Color& color, unsigned int program)
    :   Rectangle(width,height,program){
    this->color = color;
}

Vector2 Rectangle::localCenter() const {
    return {width/2,height/2};
}
