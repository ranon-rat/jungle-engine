#include <iostream>
#include <vector>
#include "SDL2/SDL.h"
#include "player.hpp"

struct Wall {
  v2f v0;
  v2f v1;

  int portal;  // if is 0 then its not a portal//portals can be in different 
};
typedef std::vector<Wall> Walls;
// i reccommend to use convex shapes for the sectors
struct Sector {
  int id;
  Walls walls;
  float zFloor;
  float zCeiling;
};
typedef std::vector<Sector> Sectors;

Sectors LoadSectors(std::string path);
void RenderSectors(SDL_Renderer *renderer,Sectors sectors, Player player);

void PlainRender(SDL_Renderer *renderer, Sectors sectors, Player player);
Wall RotateAndMoveWall(Wall wall, Player player);
