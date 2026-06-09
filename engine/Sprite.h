#pragma once

#include <unordered_map>

#include "TextureMap.h"
#include "Vector2.h"
#include "Shader.h"
#include "Vertex.h"

class Sprite {

    const Shader* program;
    TextureMap uniqueMap; // only used when a single sprite uses a texture
    const TextureMap* map;
    int index;
    Vector2 offset;
    BufferObject buffer;
    std::array<Vector2,4> vertices = {
        Vector2(0,0),
        Vector2(1,0),
        Vector2(0,1),
        Vector2(1,1)
    };
    std::array<unsigned int, 6> indices = {0, 1, 3, 0, 2, 3};
    std::pmr::unordered_map<std::string,unsigned int> locations;

    float width,height;

    void addUniform(std::string name);
    void init();

public:

    Sprite(const Texture& t, const Shader& s);
    Sprite(const Texture& t, int index, const Shader& s);
    Sprite(const Texture& t, float width, float height, const Shader& s);
    Sprite(const Texture& t, float width, float height, int index, const Shader& s);
    Sprite(const TextureMap& t, int index, const Shader& s);
    Sprite(const TextureMap& t, int index, float width, float height, const Shader& s);

    void draw() const;

    void setOffset(const Vector2& pos) {offset = pos;}
    void setIndex(int i);
    void setSize(float width, float height);
    int getIndex() const {return index;}
    const TextureMap& getMap() const {return *map;}
    const Vector2& getOffset() const {return offset;}

};