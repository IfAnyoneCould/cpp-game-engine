#pragma once
#include <SDL2/SDL.h>

#include "Vector2.h"

struct Grid {
    float cell_size; // in units
    int pixel_width = 0;
    int pixel_height = 0;
    float unit_width = 0;
    float unit_height = 0;
    Vector2 offset = Vector2{};
    bool active;

    Grid(int size, bool active,SDL_Window* window);

    //main functions
    void update();
    void draw(SDL_Renderer* renderer) const;

    //get and set
    void setPosition(const Vector2& other) {offset = other;}
    void setCellSize(float size) {cell_size = size;}

};
