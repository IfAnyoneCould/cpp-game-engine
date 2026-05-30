#pragma once
#include <vector>
#include <unordered_map>
#include <string>
#include "Vector2.h"
#include "Triangle.h"
#include "Vertex.h"
#include "Colors.h"

class Shape {
protected:
    std::vector<Triangle> triangles;
    Vector2 offset = Vector2{};
    Vector2 velocity = Vector2{};
    BufferObject buffer;
    float boundingCircleRadius;
    Color color = Colors::BLACK;
    unsigned int program;
    std::unordered_map<std::string,unsigned int> locations;

public:
    virtual ~Shape() {
        glDeleteVertexArrays(1,&buffer.VAO);
        glDeleteBuffers(1,&buffer.VBO);
    }
    Shape(const std::vector<Triangle>& triangles, unsigned int program);
    Shape(const std::vector<Triangle>& triangles, const Color& color, unsigned int program);

    [[nodiscard]] virtual std::vector<Vector2> getVertices() const;
    [[nodiscard]] Vector2 worldCenter() const;
    [[nodiscard]] virtual Vector2 localCenter() const;
    [[nodiscard]] Vector2 getOffset() const {return offset;};
    [[nodiscard]] Vector2 getVelocity() const {return velocity;};
    [[nodiscard]] bool contains(const Vector2& point);
    [[nodiscard]] bool contains(const Shape& other);
    [[nodiscard]] virtual std::vector<unsigned int> getIndices() const;
    [[nodiscard]] Color getColor() const {return color;}

    void setVelocity(const Vector2& vel);
    void addVelocity(const Vector2& vel);
    void setOffset(const Vector2& pos);
    void addOffset(const Vector2& pos);
    void setColor(const Color& color);
    void addLocation(const char* loc);

    void update(double deltaTime);
    void setUniforms() const;
    virtual void draw() const;
    virtual void genBuffer();
    void drawWireFrame() const;

};