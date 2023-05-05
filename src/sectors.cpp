#include "./sectors.hpp"

#include "graphics.hpp"
#include "math.h"
#define SCALE 200
bool IsOnCamera(Wall wall){
  float min=atan(-WIDTH/400);
  float max=atan(WIDTH/400);
  float v0angle=atan2(wall.v0.y,wall.v0.x);
  float v1angle=atan2(wall.v1.y,wall.v1.x);



}
Wall RotateAndMoveWall(Wall wall, Player player) {
  Wall w;
  float alpha = player.horizontal_angle * RAD;
  float cs = cos(alpha);
  float sn = sin(alpha);
  float x0 = wall.v0.x - player.x;
  float y0 = wall.v0.y - player.y;

  float x1 = wall.v1.x - player.x;
  float y1 = wall.v1.y - player.y;
  // rotation
  // x
  w.v0.x = x0 * cs - y0 * sn;
  w.v1.x = x1 * cs - y1 * sn;
  // y
  w.v0.y = x0 * sn + y0 * cs;
  w.v1.y = x1 * sn + y1 * cs;
  if(w.v0.y==0){
    w.v0.y=0.0001;
  }
  if(w.v1.y==0){
    w.v1.y=0.0001;
  }
  return w;
}

void RenderSectors(SDL_Renderer *renderer, Sectors sectors, Player player) {
    SDL_SetRenderDrawColor(renderer, 255,255,255, 70);

  for (Sector sector : sectors) {
    for (Wall wall : sector.walls) {
      Wall w = RotateAndMoveWall(wall, player);
      v2f pf0;
      v2f pf1;
      v2f pc0;
      v2f pc1;

      float x0 = (w.v0.x / w.v0.y) * SCALE+WIDTH/2;
      float x1 = (w.v1.x / w.v1.y) * SCALE+WIDTH/2;
      float y0=w.v0.y;
      float y1=w.v1.y;

      std::cout << x0 << " " << x1 << "\n";
            std::cout << w.v0.x << " " << w.v1.x  << "\n";


      if (x0 > x1) {
        float cx = x0;
        float cy=y0;


        x0 = x1;
        x1 = cx;
        y0=y1;
        y1=cy;
      }
      if (x0 == x1) {
        continue;
      }
      float height_camera=player.z+player.height;
      // y will beused as zs
      // floor
      pf0.x = x0;
      pf0.y = ((sector.zFloor - height_camera) / y0) *SCALE+HEIGHT/2;

      pf1.x = x1;
      pf1.y = ((sector.zFloor - height_camera) /y1) * SCALE+HEIGHT/2;
      // ceiling
      pc0.x = x0;
      pc0.y = ((sector.zFloor + sector.zCeiling - height_camera) / y0) *
              SCALE+HEIGHT/2;

      pc1.x = x1;
      pc1.y = ((sector.zFloor + sector.zCeiling - height_camera) /y1) *
           SCALE+HEIGHT/2;
      float shadow=atan2((wall.v1.y-wall.v0.y),wall.v1.x-wall.v0.y);
      draw_wall(renderer, 1, pf0, pf1, pc0, pc1,shadow/(2*M_PI));
    // SDL_RenderDrawLine(renderer, pf0.x,pf0.y,pf1.x,pf1.y);
    // SDL_RenderDrawLine(renderer, pc0.x,pc0.y,pc1.x,pc1.y);
    // SDL_RenderDrawLine(renderer, pf0.x,pf0.y,pc0.x,pc0.y);
    //SDL_RenderDrawLine(renderer, pf1.x,pf1.y,pc1.x,pc1.y);



    }
  }
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 70);
}

void PlainRender(SDL_Renderer *renderer, Sectors sectors, Player player) {
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 70);

  for (Sector sector : sectors) {
    for (Wall wall : sector.walls) {
      Wall w = RotateAndMoveWall(wall, player);
      SDL_RenderDrawLine(renderer, w.v0.x * 4 + WIDTH / 2,
                         HEIGHT / 2 - w.v0.y * 4, WIDTH / 2 + w.v1.x * 4,
                         HEIGHT / 2 - w.v1.y * 4);
    }
  }
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 70);
}