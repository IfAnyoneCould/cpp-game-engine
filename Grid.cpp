#include "Grid.h"
#include "Unit.h"

Grid::Grid(int size, bool active,SDL_Window* window) {
    this->cell_size = size;
    this->active = active;
    SDL_GetWindowSize(window, &pixel_width, &pixel_height);
    unit_width = Unit::pixelToUnit(pixel_width);
    unit_height = Unit::pixelToUnit(pixel_height);
}

void Grid::update() {
    if (active) {
        offset.x = fmod(offset.x, cell_size);
        if (offset.x < 0) offset.x += cell_size;

        offset.y = fmod(offset.y, cell_size);
        if (offset.y < 0) offset.y += cell_size;

    }
}

void Grid::draw(SDL_Renderer* renderer) const {
    SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
    int temp = 0;
    for (int x = 0; x < unit_width / cell_size + 1; x++) {
        temp = static_cast<int>(Unit::unitToPixel(x * cell_size + offset.x));
        SDL_RenderDrawLine(renderer, temp, 0, temp, pixel_height);
    }
    for (int y = 0; y < unit_height / cell_size + 1; y++) {
        temp = static_cast<int>(Unit::unitToPixel(y * cell_size + offset.y));
        SDL_RenderDrawLine(renderer, 0, temp, pixel_width, temp);
    }
}