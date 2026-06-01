#include "Vertex.h"
#include "Constants.h"
#include <glad/glad.h>

std::vector<float> Vertex::getVertexArray(const std::vector<Vector2>& vec2Array) {
    std::vector<float> array = {};
    for (const auto& v : vec2Array) {
        array.push_back(v.x / Constants::WORLD_WIDTH);
        array.push_back(v.y / Constants::WORLD_HEIGHT);
        array.push_back(0);
    }
    return array;
}

BufferObject Vertex::getBufferObjects(const std::vector<Vector2>& vertices, const std::vector<unsigned int>& indices) {
    BufferObject buffer = {0,0,0};
    std::vector<float> array = getVertexArray(vertices);

    glGenVertexArrays(1,&buffer.VAO);
    glGenBuffers(1,&buffer.VBO);
    glGenBuffers(1,&buffer.EBO);

    glBindVertexArray(buffer.VAO);

    glBindBuffer(GL_ARRAY_BUFFER,buffer.VBO);
    glBufferData(GL_ARRAY_BUFFER,array.size() * sizeof(float),array.data(),GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer.EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),indices.data(),GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER,0);

    glBindVertexArray(0);

    return buffer;

}

BufferObject Vertex::getBufferObjects(const std::vector<Vector2> &vertices) {
    BufferObject buffer = {0,0};
    std::vector<float> array = getVertexArray(vertices);

    glGenVertexArrays(1,&buffer.VAO);
    glGenBuffers(1,&buffer.VBO);

    glBindVertexArray(buffer.VAO);

    glBindBuffer(GL_ARRAY_BUFFER,buffer.VBO);
    glBufferData(GL_ARRAY_BUFFER,array.size() * sizeof(float),array.data(),GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER,0);

    glBindVertexArray(0);

    return buffer;
}
