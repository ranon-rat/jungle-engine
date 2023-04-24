#include "./sectors.hpp"

#include "math.h"

Wall RotateAndMoveWall(Wall wall, Player player) {
  Wall w;
  float alpha=player.horizontal_angle*RAD;
  float cs=cos(alpha);
  float sn=sin(alpha);
  float x0 = wall.v0.x - player.x;
  float y0 = wall.v0.y - player.y;

  float x1 = wall.v1.x - player.x;
  float y1 = wall.v1.y - player.y;
  // rotation
  //x
  w.v0.x = x0 * cs - y0 * sn;
  w.v1.x = x1 * cs - y1* sn;
  //y
  w.v0.y =x0 * sn + y0 * cs;
  w.v1.y = x1 * sn + y1* cs;
  
  return w;
}




void PlainRender(SDL_Renderer *renderer, Sectors sectors, Player player) {
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 70);

  for (Sector sector : sectors) {
    for (Wall wall : sector.walls) {
      Wall w = RotateAndMoveWall(wall, player);
      SDL_RenderDrawLine(renderer, w.v0.x*4+WIDTH/2,HEIGHT/2- w.v0.y*4,WIDTH/2+ w.v1.x*4, HEIGHT/2-w.v1.y*4);
    }
  }
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 70);
}