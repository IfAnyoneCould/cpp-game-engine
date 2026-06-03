#include "TextureMap.h"
#include <array>

std::array<Vector2,4> TextureMap::getVertices(int index) const {

    Vector2 offset = getOffset(index);

    return {
        Vector2(offset.x, offset.y),
        Vector2(offset.x + cellWidth, offset.y),
        Vector2(offset.x, offset.y + cellHeight),
        Vector2(offset.x + cellWidth, offset.y + cellHeight)
    };
}

Vector2 TextureMap::getOffset(int index) const {
    int row = index / columns;
    int column = index % columns;

    float x = column * cellWidth;
    float y = row * cellHeight;

    return {x,y};
}
