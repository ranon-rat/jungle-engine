
#include <SFML/Graphics.hpp>
#include <iostream>
#include "global.hpp"
struct Square{
    float x;
    float y;
  
    float dis;
    int kind;
    bool side;
};
class Player {
  float x = 1.5;
  float y = 1.5;
    float step_x=0;
    float step_y=0;
  float angle;

 public:
  void Move();
  void SetPos(float, float);
  void Show(sf::RenderWindow *);
  void RayCast(sf::RenderWindow *window, int lines, int map1[MAP_HEIGHT][MAP_WIDTH]);
  Square Intersect(float origin_x, float origin_y,
                                       float alpha, int map1[MAP_HEIGHT][MAP_WIDTH]) ;
};
