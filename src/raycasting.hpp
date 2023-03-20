#pragma once
#include <SDL2/SDL.h>

#include <iostream>

#include "global.hpp"
#include "player.hpp"


float Dis(float x1, float y1, float x2, float y2);
void DrawTexture(float xi, float yi, float x1, float y1, float x2, float y2,
                 float start, float end, int xw, SDL_Color color,
                 SDL_Renderer *renderer);


// this is a more kind of wolfestein 3d style
struct Square {
  float x;
  float y;
  float yc;
  float xc;

  float dis;
  int kind;
  bool side;
};

void RayCastMatrixMap(SDL_Renderer *renderer, int points[MAP_HEIGHT][MAP_WIDTH],
                      Player p);

Square IntersectDDA(float origin_x, float origin_y, float alpha,
                    int map1[MAP_HEIGHT][MAP_WIDTH]);