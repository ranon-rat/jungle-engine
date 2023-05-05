#include "./graphics.hpp"
const std::vector<SDL_Color> colors_walls = {
    {255, 255, 255, 255},
    {255, 0, 0, 255},
    {0, 255, 0, 255},
    {0, 0, 255, 255},

};
void draw_wall(SDL_Renderer *renderer, int kind, v2f p0f, v2f p1f, v2f p0c,
               v2f p1c,float shadow) {
  if (p0f.x == p1f.x||p0f.x > p1f.x) {
    std::cout << "not allowed\n";
    return;
  }
 
  // this is being used for drawing the lines that i have projected using some
  // basic equations that i will be making ceiling
  float mf = (p1f.y - p0f.y) / (p1f.x - p0f.x);
  float mc = (p1c.y - p0c.y) / (p1f.x - p0f.x);
  SDL_SetRenderDrawColor(renderer, colors_walls[kind].r*shadow, colors_walls[kind].g*shadow,
                         colors_walls[kind].b*shadow, colors_walls[kind].a*shadow);
  for (int x = fmax(p0f.x, 0); x < fmin(p1f.x, WIDTH); x++) {
    float yf = p0f.y + mf * (x - p0f.x);
    float yc = mc * (x - p0c.x) + p0c.y;

    // maube with this i can draw some kind of polygons idk

    // verline drawing
    for (int y = fmax(yf, 0); y < fmin(yc, HEIGHT); y++) {
      SDL_RenderDrawPoint(renderer, x,HEIGHT- y);
    }
  }
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 70);
}