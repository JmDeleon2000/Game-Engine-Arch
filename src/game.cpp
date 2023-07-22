#include <print.h>
#include "game.h"


Game::Game(const char* name, int width, int height) : width(width), height(height)
{
    SDL_Init(SDL_INIT_EVERYTHING);

    window = SDL_CreateWindow(name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    renderer = SDL_CreateRenderer(window, -1, 0);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    int maxFPS = 60;
    frameDuration = (1000.0f / maxFPS);  // how many mili seconds in one frame

    // initial frame count variables
    frameCount = 0;
    lastFPSUpdateTime = 0;
    FPS = 0;
    frameEndTimestamp = frameStartTimestamp = SDL_GetTicks();
}


void Game::frameStart()
{
    print("Game frame start\n");
    deltaTime = (frameEndTimestamp - frameStartTimestamp) / 1000.0f;

    vprint(deltaTime);
    frameStartTimestamp = SDL_GetTicks();
}
void Game::frameEnd()
{
    print("Game end start\n");


    frameEndTimestamp = SDL_GetTicks();
    float actualFrameDuration = frameEndTimestamp - frameStartTimestamp;

    //vprint(frameDuration);
    //vprint(actualFrameDuration);
    //FPS throttling
    if (actualFrameDuration < frameDuration)
        SDL_Delay(frameDuration - actualFrameDuration);
    
    frameEndTimestamp = SDL_GetTicks();

    frameCount++;
    // Update FPS counter every second
    Uint32 currentTime = SDL_GetTicks();
    FPS = 1 / deltaTime;
    vprint(FPS);
}
void Game::update()
{
    print("Game update\n");
}
void Game::render()
{
    print("Game rendering\n");

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 1);
    SDL_RenderClear(renderer);

    SDL_RenderPresent(renderer);

}
bool Game::running()
{
    return stateFlags & 1;
}
void Game::handleEvents()
{
    print("Handle events\n");
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0)
    {
        if (event.type == SDL_QUIT)
            stateFlags = 0;
    }
}
Game::~Game()
{
    SDL_DestroyRenderer(renderer);

    SDL_DestroyWindow(window);
    SDL_Quit();
}