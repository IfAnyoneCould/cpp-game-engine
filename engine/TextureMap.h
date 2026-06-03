#pragma once
#include "Vector2.h"
#include "Texture.h"
#include <array>

class TextureMap {
    const Texture* texture;
    int rows, columns;
    float cellWidth, cellHeight;

public:
    TextureMap() : texture(), rows(), columns(0), cellWidth(0), cellHeight(0) {};
    explicit TextureMap(const Texture& texture) : texture(&texture), cellWidth(1), cellHeight(1) {rows = 1; columns = 1;};
    TextureMap(const Texture& texture, int rows, int columns) : texture(&texture), rows(rows), columns(columns), cellWidth(1.0f/columns), cellHeight(1.0f/rows) {};

    std::array<Vector2,4> getVertices(int index) const;
    Vector2 getOffset(int index) const;
    const Texture* getTexture() const {return texture;}
    int getColumns() const {return columns;}
    int getRows() const {return rows;}
    float getCellHeight() const {return cellHeight;}
    float getCellWidth() const {return cellWidth;}
};