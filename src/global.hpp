#pragma once
#define RAD 0.0174533
#define DEG 57.2958
#define MAXANG  0.00277777777//1/360
#define TAU M_PI * 2
// rendering
#define MAX_RENDER_DISTANCE 50

#define MAP_WIDTH 24
#define MAP_HEIGHT 24
// window
#define WIDTH 1000
#define HEIGHT 800
// really importante
#define FOV_HORIZONTAL 50*RAD
#define FOV_VERTICAL 45*RAD

// texture and sprites
#define TEXTURE_HEIGHT 8
#define TEXTURE_WIDTH 8 

#define SKY_WIDTH 16
#define SKY_HEIGHT 16

struct v2f {
  float x;
  float y;
};
struct v2i {
  int x;
  int y;
};

struct v3i {
  int x;
  int y;
};
