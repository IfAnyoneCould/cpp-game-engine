#pragma once
#include "Shape.h"

class RegularPolygon : public Shape {
protected:
    float radius;
    int sides;
public:
    ~RegularPolygon() override {
        glDeleteBuffers(1,&buffer.EBO);
    }
    RegularPolygon(float radius, int sides, unsigned int program);
    RegularPolygon(float radius, int sides, const Color& color, unsigned int program);

    [[nodiscard]] std::vector<Vector2> getVertices() const override;
    [[nodiscard]] Vector2 localCenter() const override;
    [[nodiscard]] std::vector<unsigned int> getIndices() const override;
    [[nodiscard]] float getRadius() const {return radius;}
    [[nodiscard]] int getSides() const {return sides;}

    void draw() const override;
    void genBuffer() override;

};