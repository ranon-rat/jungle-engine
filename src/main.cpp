#include <iostream>

#include "SDL2/SDL.h"

#include "Engine.h"
#include "Global.h"

int main(int argc, char *argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;

        return 1;
    }

    SDL_Window *window =
        SDL_CreateWindow("Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);

    if (window == NULL)
    {
        SDL_Log("Unable to create window: %s", SDL_GetError());

        return 1;
    }

    SDL_Renderer *renderer =
        SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (renderer == NULL)
    {
        SDL_Log("Unable to create renderer: %s", SDL_GetError());

        return 1;
    }

    SDL_Bool done = SDL_FALSE;

    Engine engine = Engine(renderer);

    while (done == SDL_FALSE)
    {
        SDL_RenderClear(renderer);
        SDL_Event event;

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                done = SDL_TRUE;
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderPresent(renderer);

        SDL_Delay(1000 / 30);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
