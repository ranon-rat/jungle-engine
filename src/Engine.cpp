#include <SDL2/SDL.h>

#include <math.h>

#include "BinarySpacePartitioning.h"
#include "Engine.h"

Engine::Engine(SDL_Renderer *renderer) : renderer(renderer), binarySpacePartitioning(BinarySpacePartitioning(this))
{
    this->loader = new WADLoader("assets/DOOM.wad");
    this->player = Player();
}

void Engine::update()
{
    this->binarySpacePartitioning.update();
}

void Engine::drawSegment(Seg &seg, int subSectorId)
{
    Vertex v_1 = this->loader->vertexes[seg.startVertex];
    Vertex v_2 = this->loader->vertexes[seg.endVertex];

    SDL_RenderDrawLine(this->renderer, v_1.x, v_1.y, v_2.x, v_2.y);
}
