#pragma once

#include <unordered_map>

#include "TextureMap.h"
#include "Vector2.h"
#include "Shader.h"
#include "Vertex.h"

class Sprite {

    const Shader* program;
    const TextureMap* map;
    TextureMap uniqueMap; // only used when a single sprite uses a texture
    int index;
    Vector2 offset;
    BufferObject buffer;
    std::array<Vector2,4> vertices;
    std::array<Vector2,4> uvVertices;
    std::array<unsigned int, 6> indices = {0, 1, 2, 0, 2, 3};
    std::pmr::unordered_map<std::string,unsigned int> locations;

    float width,height;

    void addUniform(std::string name);

public:

    Sprite(const Texture& t, const Shader& s);
    Sprite(const TextureMap& t, int index, const Shader& s);

    void draw() const;

    void setOffset(const Vector2& pos) {offset = pos;}
    void setDimensions(float w, float h) {width = w; height = h;}
    const Vector2& getOffset() const {return offset;}

};