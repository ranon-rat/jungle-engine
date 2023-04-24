#include "./sectors.hpp"

#include "math.h"

Wall RotateAndMoveWall(Wall wall, Player player) {
  Wall w;
  float alpha=player.horizontal_angle*RAD;
  w.v0.x =wall.v0.x- player.x;
  w.v0.y = wall.v0.y-player.y;

  w.v1.x = wall.v1.x- player.x;
  w.v1.y =wall.v1.y- player.y;
  // rotation
  w.v0.x = w.v0.x * cos(alpha) -
           w.v0.y * sin(alpha);

  w.v0.y = w.v0.x * sin(alpha) +
           w.v0.y * cos(alpha);

  w.v1.x = w.v1.x * cos(alpha) -
           w.v1.y * sin(alpha);

  w.v1.y = w.v1.x * sin(alpha) +
           w.v1.y * cos(alpha);
  return w;
}




void PlainRender(SDL_Renderer *renderer, Sectors sectors, Player player) {
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 70);

  for (Sector sector : sectors) {
    for (Wall wall : sector.walls) {
      Wall w = RotateAndMoveWall(wall, player);
      SDL_RenderDrawLine(renderer, w.v0.x*4,HEIGHT- w.v0.y*4, w.v1.x*4, HEIGHT-w.v1.y*4);
    }
  }
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 70);
}