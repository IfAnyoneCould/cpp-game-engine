#include "RegularPolygon.h"

RegularPolygon::RegularPolygon(float radius, int sides, unsigned int program)
    : Shape([&](){
        std::vector<Triangle> tris;
        Vector2 center = Vector2{};

        float offset = 2 * Constants::PI / sides;

        for (int i = 0; i < sides; i++) {
            tris.emplace_back(center,
                Vector2::fromRadiansAndMagnitude(offset * i, radius),
                Vector2::fromRadiansAndMagnitude(offset * (i + 1),radius));
        }
        return tris;
    }(),program) {
    this->radius = radius;
    this->sides = sides;
    genBuffer();
}

RegularPolygon::RegularPolygon(float radius, int sides, const Color& color, unsigned int program)
    : RegularPolygon(radius, sides, program) {
    this->color = color;
}

Vector2 RegularPolygon::localCenter() const {
    return triangles[0].getA();
}

std::vector<Vector2> RegularPolygon::getVertices() const {
    std::vector<Vector2> vertices;
    vertices.push_back(localCenter());
    for (const auto& t : triangles) {
        vertices.push_back(t.getB());
    }
    return vertices;
}

std::vector<unsigned int> RegularPolygon::getIndices() const {
    std::vector<unsigned int> indices;
    for (int i = 1; i < sides; i++) {
        indices.push_back(0);
        indices.push_back(i);
        indices.push_back(i + 1);
    }
    indices.push_back(0);
    indices.push_back(1);
    indices.push_back(sides);

    return indices;
}

void RegularPolygon::draw() const {
    glUseProgram(program);
    setUniforms();
    glBindVertexArray(buffer.VAO);
    glDrawElements(GL_TRIANGLES,sides * 3,GL_UNSIGNED_INT,0);
}

void RegularPolygon::genBuffer() {
    this->buffer = Vertex::getBufferObjects(getVertices(),getIndices());
}
