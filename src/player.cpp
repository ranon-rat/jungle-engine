#include "player.hpp"

#include <SDL2/SDL.h>
#include <math.h>

#include <iostream>

#include "global.hpp"


void Player::Move(SDL_Event event) {
  if (event.type != SDL_KEYDOWN) return;
  switch (event.key.keysym.sym) {
    case SDLK_w:
      this->y += sin(horizontal_angle*RAD) * 0.1;
      this->x += cos(horizontal_angle*RAD) * 0.1;
      break;
    case SDLK_s:

      this->y -= sin(horizontal_angle*RAD) * 0.1;
      this->x -= cos(horizontal_angle) * 0.1;
      break;
    case SDLK_a:

      this->horizontal_angle += 1;

      break;
    case SDLK_d:

      this->horizontal_angle -= 1;

      break;
    default:
      break;
  }

  if (horizontal_angle < 0) {
    horizontal_angle += 360 ;
  }

  if (horizontal_angle > 360) {
    horizontal_angle -=360;
  }
}

void Player::Show(SDL_Renderer *renderer) {
  // SDL2 Not supports circles
  SDL_Rect rect = {(int)this->x * 10 - 5, (int)this->y * 10 - 5, 10, 10};
  SDL_Color color = {100, 0, 0, 100};
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
  SDL_RenderDrawRect(renderer,&rect);

}

void Player::SetPos(float i_x, float i_y) {
  x = i_x + .5;
  y = i_y + 0.5;
}

  