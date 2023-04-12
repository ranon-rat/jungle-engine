#include <math.h>

#include "Player.h"

#include "WAD/WADTypes.h"

Player::Player()
{
    this->x = 0;
    this->y = 0;
    this->z = 0;
    this->angle = 0;
}

float Player::pointToAngle(Vertex &vertex)
{
    float dx = vertex.x - this->player->x;
    float dy = vertex.y - this->player->y;

    float angle(atan2f(dy, dx) * 180 / M_PI);

    return angle;
}
