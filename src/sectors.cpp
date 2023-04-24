#include "./sectors.hpp"

#include "graphics.hpp"
#include "math.h"

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

  return w;
}

void RenderSectors(SDL_Renderer *renderer, Sectors sectors, Player player) {
  for (Sector sector : sectors) {
    for (Wall wall : sector.walls) {
      Wall w = RotateAndMoveWall(wall, player);
      v2f pf0;
      v2f pf1;
      v2f pc0;
      v2f pc1;

      float x0 = (w.v0.x / w.v0.y) * WIDTH / 2;
      float x1 = (w.v1.x / w.v1.y) * WIDTH / 2;
      std::cout << x0 << " " << x1 << "\n";
            std::cout << w.v0.x << " " << w.v1.x  << "\n";


      if (x0 > x1) {
        float cx = x0;
        x0 = x1;
        x1 = cx;
      }
      if (x0 == x1) {
        continue;
      }

      // y will beused as zs
      // floor
      pf0.x = x0;
      pf0.y = ((sector.zFloor - player.z) / w.v0.y) * (HEIGHT);

      pf1.x = x1;
      pf1.y = ((sector.zFloor - player.z) / w.v1.y) * (HEIGHT );
      // ceiling
      pc0.x = x0;
      pc0.y = ((sector.zFloor + sector.zCeiling - player.z) / w.v0.y) *
              (HEIGHT);

      pc1.x = x1;
      pc1.y = ((sector.zFloor + sector.zCeiling - player.z) / w.v1.y) *
              (HEIGHT );
      draw_wall(renderer, 1, pf0, pf1, pc0, pc1);
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