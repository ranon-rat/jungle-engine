#include <iostream>

#include <SDL2/SDL.h>

#include "global.hpp"
#include "map.hpp"

struct Square
{
    float x;
    float y;

    float dis;
    int kind;
    bool side;
};

Square IntersectDDA(float origin_x, float origin_y, float alpha, int map1[MAP_HEIGHT][MAP_WIDTH]);

struct Sector
{
};

class Player
{
public:
    float x = 2.5;
    float y = 2.5;

    float step_x = 0;
    float step_y = 0;

    float horizontal_angle = 0;

    World *map;

public:
    void Move();
    void SetPos(float, float);
    void Show(SDL_Renderer *renderer);
    void RayCast(SDL_Renderer *renderer, int points[MAP_HEIGHT][MAP_WIDTH]);
};
