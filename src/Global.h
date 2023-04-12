#pragma once

#include <math.h>

// Doom resolution is 320x200
#define MIN_HEIGHT 200
#define MIN_WIDTH 320

#define SCALE 3

// Scale the resolution
#define HEIGHT MIN_HEIGHT * SCALE
#define WIDTH MIN_WIDTH * SCALE

//
#define FOV 90.0
#define SCREEN_DIST HEIGHT / (tan(FOV / 2 * M_PI / 180))
