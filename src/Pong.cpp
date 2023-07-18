#include <print.h>
#include "pong.h"



Pong::Pong(const char* name, int width, int height) 
{
    SDL_Init(SDL_INIT_EVERYTHING);

    window = SDL_CreateWindow(name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    renderer = SDL_CreateRenderer(window, -1, 0);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    int maxFPS = 60;
    frameDuration = (1.0f / maxFPS) * 1000.0f;  // how many mili seconds in one frame

    // initial frame count variables
    frameCount = 0;
    lastFPSUpdateTime = 0;
    FPS = 0;
}

void  Pong::update() 
{
    print("Pong update\n");
}
void Pong::render()
{
    print("Pong render\n");

}
void Pong::handleEvents() 
{
    print("Pong events\n");
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0)
    {
        if (event.type == SDL_QUIT)
            stateFlags = 0;
    }
}