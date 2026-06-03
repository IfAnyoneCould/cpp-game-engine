#pragma once
#include "Vector2.h"
#include "Texture.h"
#include <array>

class TextureMap {
    const Texture* texture;
    int rows, columns;

public:
    TextureMap() : texture(), rows(0), columns(0) {};
    explicit TextureMap(const Texture& texture) : texture(&texture) {rows = 1; columns = 1;};
    TextureMap(const Texture& texture, int rows, int columns) : texture(&texture), rows(rows), columns(columns) {};

    std::array<Vector2,4> getVertices(int index) const;
    const Texture* getTexture() const {return texture;}
    int getColumns() const {return columns;}
    int getRows() const {return rows;}
};