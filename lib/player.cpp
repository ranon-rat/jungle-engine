#include <math.h>

#include <SDL2/SDL.h>

#include "global.hpp"
#include "map.hpp"
#include "player.hpp"

void Player::Move()
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        if (event.type != SDL_PRESSED)
            return;

        if (event.key.keysym.sym == SDLK_w)
        {
            this->y += sin(horizontal_angle) * 0.05;
            this->x += cos(horizontal_angle) * 0.05;
        }

        if (event.key.keysym.sym == SDLK_s)
        {
            this->y -= sin(horizontal_angle) * 0.05;
            this->x -= cos(horizontal_angle) * 0.05;
        }

        if (event.key.keysym.sym == SDLK_a)
        {
            this->horizontal_angle += RAD;
        }

        if (event.key.keysym.sym == SDLK_d)
        {
            this->horizontal_angle -= RAD;
        }

        if (horizontal_angle < 0)
        {
            horizontal_angle = TAU - RAD;
        }

        if (horizontal_angle > TAU)
        {
            horizontal_angle -= TAU;
        }
    }
}

void Player::Show(SDL_Renderer *renderer)
{
    // SDL2 Not supports circles
    SDL_Rect rect = {this->x * 10 - 5, this->y * 10 - 5, 10, 10};
    SDL_Color color = {255, 0, 0, 255};

    this->map->drawWall(renderer, rect, color);

    /*sf::CircleShape circle(5);
    circle.setPosition(sf::Vector2f(this->x * 10 - 5, this->y * 10 - 5));
    circle.setFillColor(sf::Color::Blue);
    window->draw(circle);
    circle.setRadius(50);
    circle.setOutlineThickness(2);
    circle.setOutlineColor(sf::Color::White);

    circle.setPosition(sf::Vector2f(WIDTH - 100, 0));
    circle.setFillColor(sf::Color::Blue);

    window->draw(circle);
    sf::Vertex line[] = {
        sf::Vector2f(WIDTH - 50, 50),
        sf::Vector2f(WIDTH - 50 + cos(horizontal_angle) * 50, 50 + sin(horizontal_angle) * 50)};

    window->draw(line, 2, sf::Lines);*/
}

void Player::SetPos(float i_x, float i_y)
{
    x = i_x + .5;
    y = i_y + 0.5;
}

void Player::RayCast(SDL_Renderer *renderer, int map1[MAP_HEIGHT][MAP_WIDTH])
{
    float proj_dis = 0.5 * 5 / tan(50 * RAD);

    for (float xw = 0; xw <= WIDTH; xw++)
    {

        float alpha = FOV_VERTICAL * (floor(0.5 * WIDTH - xw) / (WIDTH - 1)) + horizontal_angle;
        Square inter = IntersectDDA(x, y, alpha, map1);
        if (inter.kind == 0)
        {
            return;
        }

        //sf::Color color;
        SDL_Color color;
        switch (inter.kind)
        {
            case 1:
                color = {255 * (1 - inter.dis / MAX_RENDER_DISTANCE) - ((inter.side) ? 50 : 0), 0, 0, 255};
                break;
            
            case 2:
                color = {0, 0, 255 * (1 - inter.dis / MAX_RENDER_DISTANCE) - ((inter.side) ? 50 : 0), 255};
                break;
            
            case 3:
                color = {255 * (1 - inter.dis / MAX_RENDER_DISTANCE) - ((inter.side) ? 50 : 0), 255 * (1 - inter.dis / MAX_RENDER_DISTANCE) - ((inter.side) ? 10 : 0), 255 * (1 - inter.dis / MAX_RENDER_DISTANCE) - ((inter.side) ? 10 : 0), 255};
                break;

            case 4:
                color = {0, 255 * (1 - inter.dis / MAX_RENDER_DISTANCE) - ((inter.side) ? 50 : 0), 0, 255};
                break;

            case 5:
                color = {255 * (1 - inter.dis / MAX_RENDER_DISTANCE) - ((inter.side) ? 50 : 0), 255 * (1 - inter.dis / MAX_RENDER_DISTANCE) - ((inter.side) ? 50 : 0), 255 * (1 - inter.dis / MAX_RENDER_DISTANCE) - ((inter.side) ? 50 : 0), 255};
                break;

            default:
                color = {255, 255, 255, 255};
                break;

        /*case 1:
            color = sf::Color((255 * (1 - inter.dis / MAX_RENDER_DISTANCE)) -
                                  ((inter.side) ? 50 : 0),
                              0, 0);
            break;
        case 2:
            color = sf::Color(0, 0,
                              (255 * (1 - inter.dis / MAX_RENDER_DISTANCE)) -
                                  ((inter.side) ? 50 : 0));

            break;
        case 3:
            color = sf::Color((255 * (1 - inter.dis / MAX_RENDER_DISTANCE)) -
                                  ((inter.side) ? 50 : 0),
                              (255 * (1 - inter.dis / MAX_RENDER_DISTANCE)) -
                                  ((inter.side) ? 10 : 0),
                              (255 * (1 - inter.dis / MAX_RENDER_DISTANCE)) -
                                  ((inter.side) ? 10 : 0));
            break;
        case 4:
            color = sf::Color(0,
                              (255 * (1 - inter.dis / MAX_RENDER_DISTANCE)) -
                                  ((inter.side) ? 50 : 0),
                              0);

            break;
        default:
            color = sf::Color((55 * (1 - inter.dis / MAX_RENDER_DISTANCE)) -
                                  ((inter.side) ? 50 : 0),
                              (55 * (1 - inter.dis / MAX_RENDER_DISTANCE)) -
                                  ((inter.side) ? 10 : 0),
                              (55 * (1 - inter.dis / MAX_RENDER_DISTANCE)) -
                                  ((inter.side) ? 10 : 0));

            break;*/
        }
        float height =
            (HEIGHT * proj_dis /
             (inter.dis * cos(alpha - horizontal_angle)));
        //sf::RectangleShape line(sf::Vector2f(1, height));

        SDL_Rect line = {xw, 0.5 * (HEIGHT - height), 1, height};

        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        SDL_RenderFillRect(renderer, &line);



        //line.setFillColor(color);
        //line.setPosition(sf::Vector2f(xw, 0.5 * (HEIGHT - height)));

        //window->draw(line);
    }
}
Square IntersectDDA(float origin_x, float origin_y, float alpha,
                    int map1[MAP_HEIGHT][MAP_WIDTH])
{
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

    double x_unit = (cos(alpha) == 0)
                        ? 1
                        : std::abs(1 / cos(alpha)); // sqrt(1+tan(alpha)^2);
    double y_unit = (sin(alpha) == 0)
                        ? 1
                        : std::abs(1 / sin(alpha)); // sqrt(1+(1/tan(alpha))^ 2);
    // this will be used
    float ray_dist_y = 0;
    float ray_dist_x = 0;

    int step_y = 1;
    int step_x = 1;
    // i need to know the direction so i used this, its really simple
    if (cos(alpha) < 0)
    {
        step_x = -1;
        ray_dist_x = (ray_x - float(check_ray_x)) * x_unit;
    }
    else
    {
        ray_dist_x = (float(check_ray_x + 1) - ray_x) * x_unit;
    }
    if (sin(alpha) < 0)
    {
        step_y = -1;
        ray_dist_y = (origin_y - float(check_ray_y)) * y_unit;
    }
    else
    {
        ray_dist_y = (float(check_ray_y + 1) - ray_y) * y_unit;
    }
    float dis = 0;
    bool tileFound = false;
    bool side = false;
    while (dis < MAX_RENDER_DISTANCE && !tileFound)
    {
        // if the length of the x rect is bigger than y then i do this

        // you vill be happy and you will not have ze bugz

        if (ray_dist_x < ray_dist_y)
        {
            check_ray_x += step_x;
            dis = ray_dist_x;
            ray_dist_x += x_unit;
            side = true;
        }
        else
        {
            check_ray_y += step_y;
            dis = ray_dist_y;
            ray_dist_y += y_unit;
            side = false;
        }
        if (check_ray_x >= 0 && check_ray_x < MAP_WIDTH && check_ray_y >= 0 &&
            check_ray_y < MAP_HEIGHT)
        {
            tileFound = (map1[check_ray_y][check_ray_x] > 0);
        }
    }
    if (!tileFound)
    {
        dis = MAX_RENDER_DISTANCE;
    }

    y_ray_intersection = origin_y + sin(alpha) * dis;
    x_ray_intersection = origin_x + cos(alpha) * dis;

    return Square{
        .x = x_ray_intersection,
        .y = y_ray_intersection,
        .dis = dis,
        .kind = map1[check_ray_y][check_ray_x],
        .side = side,

    };
}