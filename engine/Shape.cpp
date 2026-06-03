#include "Shape.h"
#include <iostream>
#include <map>
#include "Geometry.h"
#include "Mat4.h"

std::vector<Vector2> Shape::getVertices() const {
    std::vector<Vector2> vertices;
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


Shape::Shape(const std::vector<Triangle> &triangles, const Shader& program)
    : triangles(triangles), vertices(getVertices()), normals(getNormals()), nonParallelNormals(Geometry::removeParallelVectors(normals)),
      boundingCircleRadius(0), program(&program){

    const Vector2 center = localCenter();

    for (const auto& v : vertices) {
        float distance = center.distanceTo(v);
        if (distance > boundingCircleRadius) boundingCircleRadius = distance;
    }

    addLocation("color");
    addLocation("model");
    addLocation("useTexture");

}

Shape::Shape(const std::vector<Triangle> &triangles, const Color& color, const Shader& program)
    : Shape(triangles,program) {
    this->color = color;
}

Vector2 Shape::worldCenter() const {
    return localCenter()+offset;
}

std::vector<unsigned int> Shape::getIndices() const {
    std::vector<unsigned int> indices;

    for (int i = 0; i < triangles.size(); i++) {
        indices.push_back(i * 3);
        indices.push_back(i * 3 + 1);
        indices.push_back(i * 3 + 2);
    }

    return indices;
}

void Shape::draw() const {

    program->use();
    setUniforms();
    glBindVertexArray(buffer.VAO);
    glDrawArrays(GL_TRIANGLES,0,triangles.size() * 3);
}

void Shape::genBuffer() {
    this->buffer = Vertex::getBufferObjects(vertices);
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

void Shape::setColor(const Color& color) {
    this->color = color;
}

void Shape::addLocation(const char* loc) {
    locations[loc] = glGetUniformLocation(program->getId(),loc);
}

void Shape::setUniforms() const {
    Mat4 model = Mat4::translate(offset);
    glUniformMatrix4fv(locations.at("model"),1,GL_FALSE,model.getM());
    glUniform3f(locations.at("color"),color.r,color.g,color.b);
    glUniform1i(locations.at("useTexture"),0);
}

bool Shape::intersects(const Shape &other) const {

    if (!intersectsBoundingCircle(other)) return false;

    for (const auto& t1 : triangles) {
        Triangle t1Offset = t1.translated(offset);
        for (const auto& t2 : other.triangles) {
            if (t1Offset.intersects(t2.translated(other.offset))) {return true;}
        }
    }

    return false;
}

bool Shape::contains(const Vector2 &point) const {
    for (const auto& t : triangles) {
        if (t.contains(point)) return true;
    }
    return false;
}

std::vector<Vector2> Shape::getNormals() const {

    std::map<std::pair<Vector2,Vector2>,int> edgeCount;

    for (const auto& t : triangles) {
        auto addEdge = [&](Vector2 a, Vector2 b) {
            if (b < a) std::swap(a,b);
            edgeCount[{a,b}]++;
        };
        addEdge(t.getA(),t.getB());
        addEdge(t.getB(),t.getC());
        addEdge(t.getC(),t.getA());
    }

    std::vector<Vector2> axis;

    for (auto& [edge,count] : edgeCount) {
        if (count == 1) {
            Vector2 e = edge.second - edge.first;
            axis.push_back(e.perp().normalized());
        }
    }

    return axis;
}

Vector2 Shape::project(const Vector2 &axis) const {
    float min = axis.dot(vertices[0] + offset);
    float max = min;

    for (int i = 1; i < vertices.size(); i++) {
        float p = axis.dot(vertices[i] + offset);
        if (p < min) {
            min = p;
        } else if (p > max) {
            max = p;
        }
    }
    return {min,max};
}

Collision Shape::intersectsSAT(const Shape &other) const {

    if (!intersectsBoundingCircle(other)) {
        return {};
    }

    const std::vector<Vector2> axes[2] = {nonParallelNormals, other.nonParallelNormals};

    float overlap = 99999999999;
    Vector2 smallest;

    for (int j = 0; j < 2; j++) {
        for (int i = 0; i < axes[j].size(); i++) {
            Vector2 p1 = project(axes[j][i]);
            Vector2 p2 = other.project(axes[j][i]);

            float o = Geometry::getOverlap(p1.x,p1.y,p2.x,p2.y);

            if (o < 0) {
                return {};
            }
            if (o < overlap) {
                overlap = o;
                smallest = axes[j][i];
            }
        }
    }
    Vector2 direction = worldCenter() - other.worldCenter();
    if (Vector2::dot(direction, smallest) < 0) smallest = -smallest;
    return {true, smallest, overlap};
}

void Shape::drawNormals() const {
    for (const auto& v : normals) {
        Geometry::drawLine(worldCenter(),worldCenter() + v * 50.0f,*program);
    }
}

bool Shape::intersectsBoundingCircle(const Shape &other) const {
    return worldCenter().distanceToSquared(other.worldCenter()) <=
       (boundingCircleRadius + other.boundingCircleRadius) *
       (boundingCircleRadius + other.boundingCircleRadius);
}

void Shape::draw(const Vector2& position) const {
    Mat4 model = Mat4::translate(position);
    program->use();
    glUniformMatrix4fv(locations.at("model"),1,GL_FALSE,model.getM());
    glBindVertexArray(buffer.VAO);
    glDrawArrays(GL_TRIANGLES,0,triangles.size() * 3);
}
