#include "TextureMap.h"
#include <array>

std::array<Vector2,4> TextureMap::getVertices(int index) const {
    int row = index / columns;
    int column = index % columns;

    float cellWidth = 1.0f / columns;
    float cellHeight = 1.0f / rows;

    float x = column * cellWidth;
    float y = row * cellHeight;

    return {
        Vector2(x, y),
        Vector2(x + cellWidth, y),
        Vector2(x, y + cellHeight),
        Vector2(x + cellWidth, y + cellHeight)
    };
}
