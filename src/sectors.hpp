#include <iostream>
#include <vector>

#include "player.hpp"

struct Wall {
  v2i v0;
  v2i v1;

  int portal;  // if is 0 then its not a portal
};
typedef std::vector<Wall> Walls;
struct Sector {
  int id;
  Walls walls;
  float zFloor;
  float zCeiling;
};
typedef std::vector<Sector> Sectors;

Sectors LoadSectors(std::string path);
