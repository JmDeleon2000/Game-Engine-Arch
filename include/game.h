#pragma once
#include <string>
#include <SDL.h>

class Game
{
public:

    int width;
    int height;
    int stateFlags = 1;
    float frameDuration;
    int frameCount;
    float FPS;
    Uint32 lastFPSUpdateTime;
    Uint32 frameStartTimestamp;
    Uint32 frameEndTimestamp;
    float deltaTime;

    Game(const char* name, int width, int height);
    Game();


    void frameStart();
    void frameEnd();
    virtual void update();
    virtual void render();
    virtual void handleEvents();
    bool running();
    ~Game();
    SDL_Window* window;
    SDL_Renderer* renderer;
};
