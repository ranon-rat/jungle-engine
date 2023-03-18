
#include <SFML/Graphics.hpp>
#include <iostream>

#include "global.hpp"
struct Square {
  float x;
  float y;

  float dis;
  int kind;
  bool side;
};
struct Sector{};
class Player {
  float x = 2.5;
  float y = 2.5;
  float step_x = 0;
  float step_y = 0;
  float horizontal_angle = 0;

 public:
  void Move();
  void SetPos(float, float);
  void Show(sf::RenderWindow *);
  void RayCast(sf::RenderWindow *window,
               int map1[MAP_HEIGHT][MAP_WIDTH]);

};

  Square IntersectDDA(float origin_x, float origin_y, float alpha,
                   int map1[MAP_HEIGHT][MAP_WIDTH]);