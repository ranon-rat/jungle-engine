#pragma once
#include <SDL2/SDL.h>

#include <vector>

#include "headers/global.hpp"

using namespace std;

class World
{
public:
    int points[MAP_HEIGHT][MAP_WIDTH];

    void drawWall(SDL_Renderer *renderer, SDL_Rect rect, SDL_Color color);
    void draw(SDL_Renderer *renderer);

    World(int points[MAP_HEIGHT][MAP_WIDTH]);
};
