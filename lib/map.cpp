#include <SDL2/SDL.h>

#include <vector>

#include "global.hpp"
#include "map.hpp"

using namespace std;

void World::drawWall(SDL_Renderer *renderer, SDL_Rect rect, SDL_Color color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawRect(renderer, &rect);
}

void World::draw(SDL_Renderer *renderer)
{
    for (int y = 0; y < MAP_HEIGHT; y++)
    {
        for (int x = 0; x < MAP_WIDTH; x++)
        {
            /// defino las caracteristicas de los sectores
            SDL_Rect wall = {x * 10, y * 10, 10, 10};
            SDL_Color color;

            switch (this->points[y][x])
            {
            case 1:
                color = {255, 0, 0, 255};
                break;
            case 2:
                color = {0, 0, 255, 255};
                break;
            case 3:
                color = {255, 255, 255, 255};
                break;
            case 4:
                color = {0, 255, 0, 255};
                break;
            default:
                color = {255, 255, 0, 255};
                break;
            }

            drawWall(renderer, wall, color);
        }
    }
}

World::World(int points[MAP_HEIGHT][MAP_WIDTH])
{
    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < MAP_WIDTH; j++) {
            this->points[i][j] = points[i][j];
        }
    }
}
