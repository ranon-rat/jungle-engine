
#include "raycasting.hpp"

#include <cstring>
#include "texture.hpp"



void RayCastMatrixMap(SDL_Renderer *renderer, int points[MAP_HEIGHT][MAP_WIDTH],
                      Player p) {
  float proj_dis = 0.5 * 5 / tan(FOV_VERTICAL);

  for (float xw = 0; xw <= WIDTH; xw++) {
    float alpha = FOV_HORIZONTAL * (floor(0.5 * WIDTH - xw) / (WIDTH - 1)) +
                  p.horizontal_angle;

    Square inter = IntersectDDA(p.x, p.y, alpha, points);
    // so i need to know if i have intersect to something
    // so i use this property for that
    if (!inter.found) continue;
    // i use the distance for calculating the brightness, obviously i use fmin
    // because the distance can be bigger than the max_render_distance so yeah
    float brightness =
        (1 - fmin(inter.dis, MAX_RENDER_DISTANCE) / (MAX_RENDER_DISTANCE)) *
        ((inter.side) ? 0.5 : 1);

    int texture[TEXTURE_HEIGHT * TEXTURE_WIDTH];

    SDL_Color color;
    switch (inter.kind) {
      case 1:
        color = {Uint8(70 * brightness), 0, 0, 255};
        std::memcpy(texture, texture1, sizeof(texture));
        break;

      case 2:
        color = {0, 0, Uint8(70 * brightness), 255};
        std::memcpy(texture, texture2, sizeof(texture));

        break;

      case 3:
        color = {Uint8(70 * brightness), Uint8(70 * brightness),
                 Uint8(70 * brightness), 255};
        std::memcpy(texture, texture1, sizeof(texture));

        break;

      case 4:

        color = {0, Uint8(70 * brightness), 0, 255};
        std::memcpy(texture, texture2, sizeof(texture));

        break;

      default:
        color = {Uint8(70 * brightness), 0, Uint8(70 * brightness), 255};
        std::memcpy(texture, texture1, sizeof(texture));

        break;
    }
    float height =
        (HEIGHT * proj_dis / (inter.dis * cos(alpha - p.horizontal_angle)));
    float y0 = 0.5 * (HEIGHT - height);
    float y1 = 0.5 * (HEIGHT + height);
    if (inter.side)
      DrawTextureSquare(inter.y, inter.yc, y0, y1, xw, color, texture,
                        renderer);
    else
      DrawTextureSquare(inter.x, inter.xc, y0, y1, xw, color, texture,
                        renderer);
  }

  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 70);
}

void DrawSky(Player player, SDL_Renderer *renderer) {
  for (int y = 0; y < HEIGHT; y++) {
    int u = int((float(y) / HEIGHT) * SKY_HEIGHT);

    for (int x = 0; x < WIDTH; x++) {
     int xo =SKY_WIDTH* ((player.horizontal_angle / RAD) * 3 - float(x))/(360*3);
      if (xo < 0) xo += SKY_WIDTH;


      int p = sky[u * SKY_WIDTH + (xo)%SKY_WIDTH];
      // it works the same as the other
      SDL_SetRenderDrawColor(renderer, 20 * p, 0, 20 * p, 255);
      SDL_RenderDrawPoint(renderer, x, y);
    }
  }
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 70);
  // for drawing the sky we only need to do the next
  // we get the angle that we are seeing
  // we get the column
  // then we draw it
  // the sky needs to be draw first
  // before doing the raycasting
}

void DrawTextureSquare(float xi, float x0, float start, float end, int xw,
                       SDL_Color color,
                       int texture[TEXTURE_HEIGHT * TEXTURE_WIDTH],
                       SDL_Renderer *renderer) {
  int i = (abs(xi - x0) * 8);
  // just use the distance from point b to point a, but is just a square so i
  // dont need to do that much so yeah
  for (int u = fmax(start, 0); u < fmin(end, HEIGHT); u++) {
    int v = (u - start) / abs(end - start) * 8;
    int p = texture[v * TEXTURE_WIDTH + i];
    // it works the same as the other

    SDL_SetRenderDrawColor(renderer, color.r * p, color.g * p, color.b * p,
                           color.a * p);
    SDL_RenderDrawPoint(renderer, xw, u);
  }
}

// xi and yi are the coordinates of intersection
// x1,y1 are the starting point of the polygon, lets call it a
// x2,y2 are the end point of the polygon lets call it b
// start and end are the y coordinates on the screen to draw the texture
// same for xw but its the x coordinate of the screen

void DrawTexture(float xi, float yi, float x1, float y1, float x2, float y2,
                 float start, float end, int xw, SDL_Color color,
                 SDL_Renderer *renderer) {
  float wallLength = Dis(x1, y1, x2, y2);
  // idk
  int i = (Dis(x1, y1, xi, yi) / wallLength) * 7;
  for (int u = fmax(start, 0); u < fmin(end, HEIGHT); u++) {
    int v = (u - start) / abs(end - start) * 7;
    int p = texture1[v * TEXTURE_WIDTH + i];

    SDL_SetRenderDrawColor(renderer, color.r * p, color.g * p, color.b * p,
                           color.a * p);

    SDL_RenderDrawPoint(renderer, xw, u);
  }
};

float Dis(float x1, float y1, float x2, float y2) {
  return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}
Square IntersectDDA(float origin_x, float origin_y, float alpha,
                    int map1[MAP_HEIGHT][MAP_WIDTH]) {
  // position in the map
  int check_ray_x = int(origin_x);
  int check_ray_y = int(origin_y);
  // origin of the rays
  float ray_x = origin_x;
  float ray_y = origin_y;
  // points of intersection
  float y_ray_intersection;
  float x_ray_intersection;

  // this will be used for knowing the line size depending of wich direction we
  // are using
  // with this i get the distance of each square using the rect
  // so this is really useful
  double x_unit = (cos(alpha) == 0)
                      ? 1
                      : std::abs(1 / cos(alpha));  // sqrt(1+tan(alpha)^2);
  double y_unit = (sin(alpha) == 0)
                      ? 1
                      : std::abs(1 / sin(alpha));  // sqrt(1+(1/tan(alpha))^ 2);
  // this will be used
  float ray_dist_y = 0;
  float ray_dist_x = 0;

  int step_y = 1;
  int step_x = 1;
  // i need to know the direction so i used this, its really simple
  if (cos(alpha) < 0) {
    step_x = -1;
    ray_dist_x = (ray_x - float(check_ray_x)) * x_unit;
  } else {
    ray_dist_x = (float(check_ray_x + 1) - ray_x) * x_unit;
  }
  if (sin(alpha) < 0) {
    step_y = -1;
    ray_dist_y = (origin_y - float(check_ray_y)) * y_unit;
  } else {
    ray_dist_y = (float(check_ray_y + 1) - ray_y) * y_unit;
  }
  float dis = 0;
  bool tileFound = false;
  bool side = false;
  while (dis < MAX_RENDER_DISTANCE && !tileFound) {
    // if the length of the x rect is bigger than y then i do this

    // you vill be happy and you will not have ze bugz

    if (ray_dist_x < ray_dist_y) {
      check_ray_x += step_x;
      dis = ray_dist_x;
      ray_dist_x += x_unit;
      side = true;
    } else {
      check_ray_y += step_y;
      dis = ray_dist_y;
      ray_dist_y += y_unit;
      side = false;
    }
    if (check_ray_x >= 0 && check_ray_x < MAP_WIDTH && check_ray_y >= 0 &&
        check_ray_y < MAP_HEIGHT) {
      tileFound = (map1[check_ray_y][check_ray_x] > 0);
    }
  }
  // is just a basic vector
  // i just need to know the angle and how big it is
  // and i know it so i dont need to much
  y_ray_intersection = origin_y + sin(alpha) * dis;
  x_ray_intersection = origin_x + cos(alpha) * dis;

  return Square{
      .x = x_ray_intersection,
      .y = y_ray_intersection,
      .yc = (float)check_ray_y,
      .xc = (float)check_ray_x,
      .dis = dis,
      .kind = map1[check_ray_y][check_ray_x],
      .side = side,
      .found = tileFound,

  };
}