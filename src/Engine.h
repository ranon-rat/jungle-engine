#pragma once

#include "SDL2/SDL.h"

#include <vector>

#include "BinarySpacePartitioning.h"
#include "Player.h"
#include "WAD/WADLoader.h"

class Engine
{
public:
    SDL_Renderer *renderer;
    WADLoader *loader;
    Player player;

public:
    BinarySpacePartitioning binarySpacePartitioning;

public:
    Engine(SDL_Renderer *renderer);

public:
    void drawSegment(Seg &seg, int subSectorId);

public:
    void update();
};
