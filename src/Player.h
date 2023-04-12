#pragma once

#include <math.h>

#include "WAD/WADTypes.h"

class Player
{
public:
    float x;
    float y;
    float z;
    float angle;

public:
    Player();

public:
    float pointToAngle(Vertex &vertex); 

public:
    void update();
};
