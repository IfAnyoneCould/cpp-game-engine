#pragma once
#include <vector>
#include "Vector2.h"

struct BufferObject {
    unsigned int VAO, VBO, EBO;
};

class Vertex {
public:
    static std::vector<float> getVertexArray(const std::vector<Vector2>& vec2Array);
    static BufferObject getBufferObjects(const std::vector<Vector2> &vertices, const std::vector<unsigned int>& indices);
    static BufferObject getBufferObjects(const std::vector<Vector2> &vertices);
};