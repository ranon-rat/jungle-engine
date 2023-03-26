#pragma once
#include <SDL2/SDL.h>

#include <iostream>

#include "global.hpp"
#include "map.hpp"

struct Sector {};

class Player {

 public:
  float horizontal_angle = 0;

  float x = 1.5;
  float y = 1.5;
  float z = 0;  // z works as the height

  float step_x = 0;
  float step_y = 0;

 public:
  void Move(SDL_Event event);
  void SetPos(float, float);
  void Show(SDL_Renderer *renderer);
};
