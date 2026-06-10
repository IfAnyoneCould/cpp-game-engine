#pragma once
#include <vector>
#include <unordered_map>
#include <string>
#include "Vector2.h"
#include "Triangle.h"
#include "Vertex.h"
#include "Colors.h"
#include "Vectors.h"
#include "Shader.h"

struct Collision {
    bool collided;
    Vector2 normal;
    float depth;

    Collision(bool collided, Vector2 normal, float depth) {this->collided = collided; this->normal = normal; this->depth = depth;}
    Collision() : collided(false), normal(Vectors::ZERO), depth(0.0f) {}
};

struct AABB {
    float left,right,top,bottom;
};

class Shape {
protected:
    std::vector<Triangle> triangles;
    std::vector<Vector2> vertices;
    std::vector<Vector2> normals;
    std::vector<Vector2> nonParallelNormals;
    Vector2 offset = Vector2{};
    BufferObject buffer;
    float boundingCircleRadius;
    Color color = Colors::BLACK;
    const Shader* program;
    std::unordered_map<std::string,unsigned int> locations;
    bool rect = false;

    void setRect(bool r) {rect = r;}

public:
    virtual ~Shape() {
        glDeleteVertexArrays(1,&buffer.VAO);
        glDeleteBuffers(1,&buffer.VBO);
    }
    Shape(const std::vector<Triangle>& triangles, const Shader& program);
    Shape(const std::vector<Triangle>& triangles, const Color& color, const Shader& program);

    virtual std::vector<Vector2> getVertices() const;
    Vector2 worldCenter() const;
    virtual Vector2 localCenter() const;
    Vector2 getOffset() const {return offset;};
    bool isRect() const {return rect;}
    virtual std::vector<unsigned int> getIndices() const;
    Color getColor() const {return color;}
    std::vector<Vector2> getNormals() const;
    Vector2 project(const Vector2& axis) const;
    AABB getAABB() const;

    [[nodiscard]] virtual bool contains(const Vector2& point) const;
    [[nodiscard]] bool intersectsBoundingCircle(const Shape& other) const;
    [[nodiscard]] bool intersects(const Shape& other) const;
    [[nodiscard]] Collision intersectsSAT(const Shape& other) const;
    [[nodiscard]] Collision intersectsAABB(const Shape& other) const;

    void setOffset(const Vector2& pos);
    void addOffset(const Vector2& pos);
    void setColor(const Color& color);
    void addLocation(const char* loc);

    void setUniforms() const;
    virtual void draw() const;
    virtual void draw(const Vector2& position) const;
    virtual void genBuffer();
    void drawWireFrame() const;
    void drawNormals() const;


};