#pragma once
#include <vector>
#include <unordered_map>
#include <string>
#include "Vector2.h"
#include "Triangle.h"
#include "Vertex.h"
#include "Colors.h"
#include "Vectors.h"

struct Collision {
    bool collided;
    Vector2 normal;
    float depth;

    Collision(bool collided, Vector2 normal, float depth) {this->collided = collided; this->normal = normal; this->depth = depth;}
    Collision() : collided(false), normal(Vectors::ZERO), depth(0.0f) {}
};

class Shape {
protected:
    std::vector<Triangle> triangles;
    std::vector<Vector2> vertices;
    Vector2 offset = Vector2{};
    BufferObject buffer;
    float boundingCircleRadius;
    Color color = Colors::BLACK;
    unsigned int program;
    std::unordered_map<std::string,unsigned int> locations;
    bool fixed = false;

public:
    virtual ~Shape() {
        glDeleteVertexArrays(1,&buffer.VAO);
        glDeleteBuffers(1,&buffer.VBO);
    }
    Shape(const std::vector<Triangle>& triangles, unsigned int program);
    Shape(const std::vector<Triangle>& triangles, const Color& color, unsigned int program);

    virtual std::vector<Vector2> getVertices() const;
    Vector2 worldCenter() const;
    virtual Vector2 localCenter() const;
    Vector2 getOffset() const {return offset;};
    [[nodiscard]] virtual bool contains(const Vector2& point) const;
    [[nodiscard]] bool intersects(const Shape& other) const;
    virtual std::vector<unsigned int> getIndices() const;
    Color getColor() const {return color;}
    bool isFixed() const {return fixed;}
    std::vector<Vector2> getNormals() const;
    Collision intersectsSAT(const Shape& other) const;
    Vector2 project(const Vector2& axis) const;

    void setOffset(const Vector2& pos);
    void addOffset(const Vector2& pos);
    void setColor(const Color& color);
    void addLocation(const char* loc);

    void setUniforms() const;
    virtual void draw() const;
    virtual void genBuffer();
    void drawWireFrame() const;


};