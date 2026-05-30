#include "Shape.h"
#include <unordered_set>

std::vector<Vector2> Shape::getVertices() const {
    std::vector<Vector2> vertices ;
    for (const auto& t : triangles) {
        vertices.push_back(t.getA());
        vertices.push_back(t.getB());
        vertices.push_back(t.getC());
    }

    return vertices;
}

Vector2 Shape::localCenter() const {
    Vector2 center = Vector2{};
    for (const auto& t : triangles) {
        center += t.centroid();
    }
    return center/=triangles.size();
}

Shape::Shape(const std::vector<Triangle> &triangles, unsigned int program)
    : triangles(triangles), buffer({0,0}), boundingCircleRadius(0), program(program){

    const Vector2 center = localCenter();
    const std::vector<Vector2> vertices = getVertices();

    for (const auto& v : vertices) {
        float distance = center.distanceTo(v);
        if (distance > boundingCircleRadius) boundingCircleRadius = distance;
    }
}

Shape::Shape(const std::vector<Triangle> &triangles, Color color, unsigned int program)
    : Shape(triangles,program) {
    this->color = color;
}

Vector2 Shape::worldCenter() const {
    return localCenter()+offset;
}

void Shape::addVelocity(const Vector2 &vel) {
    this->velocity+=vel;
}

void Shape::setVelocity(const Vector2 &vel) {
    this->velocity = vel;
}

void Shape::update(double deltaTime) {
    offset+=velocity * deltaTime;
}

std::vector<unsigned int> Shape::getIndices() const {
    std::vector<Vector2> vertices = getVertices();
    std::vector<unsigned int> indices;

    for (int i = 0; i < triangles.size(); i++) {
        indices.push_back(i * 3);
        indices.push_back(i * 3 + 1);
        indices.push_back(i * 3 + 2);
    }

    return indices;
}

void Shape::draw() const {
    glUseProgram(program);
    setUniformPosition();
    setUnifromColor();
    glBindVertexArray(buffer.VAO);
    glDrawArrays(GL_TRIANGLES,0,triangles.size() * 3);
}

void Shape::genBuffer() {
    this->buffer = Vertex::getBufferObjects(getVertices());
}

void Shape::drawWireFrame() const {
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    draw();
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
}

void Shape::setOffset(const Vector2 &pos) {
    this->offset = pos;
}

void Shape::addOffset(const Vector2 &pos) {
    this->offset += pos;
}

void Shape::setUniformPosition() const {
    int loc = glGetUniformLocation(program,"offset");
    glUniform2f(loc,offset.x / Constants::WORLD_WIDTH,offset.y / Constants::WORLD_HEIGHT);
}

void Shape::setColor(const Color& color) {
    this->color = color;
}

void Shape::setUnifromColor() const {
    int loc = glGetUniformLocation(program, "color");
    glUniform3f(loc,color.r,color.g,color.b);
}
