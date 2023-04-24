#include "./graphics.hpp"

void draw_wall(SDL_Renderer *renderer, int kind, v2f p0f, v2f p1f, v2f p0c,
               v2f p1c) {
  if (p0f.x == p1f.x && p0f.y == p1f.y) {
    return;
  }

  // this is being used for drawing the lines that i have projected using some
  // basic equations that i will be making ceiling
  float mf = (p1f.y - p0f.y) / (p1f.x - p0f.x);
  float mc = (p1c.y - p0c.y) / (p1c.x - p0c.x);
  SDL_SetRenderDrawColor(renderer, colors[kind].r, colors[kind].g,
                         colors[kind].b, colors[kind].a);
  for (int x = fmax(p0f.x,0); x < fmin(p1f.x,WIDTH); x++) {
    float yf = mf * x;
    float yc = mc * x;
    // verline drawing
    for (int y = fmax(yc,0); y < fmin(yf,HEIGHT); y++) {
      SDL_RenderDrawPoint(renderer, x, y);
    }
  }
}