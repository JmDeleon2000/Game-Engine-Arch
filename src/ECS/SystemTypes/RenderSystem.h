#pragma once
#include <SDL.h>
#include "ECS/System.h"

class RenderSystem : public System {
  public:
    virtual void run(SDL_Renderer* renderer) = 0;
};