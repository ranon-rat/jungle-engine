#pragma once
#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include "./global.hpp"



void draw_wall(SDL_Renderer *renderer, int kind, v2f p0f, v2f p1f, v2f p0c,
               v2f p1c,float shadow);