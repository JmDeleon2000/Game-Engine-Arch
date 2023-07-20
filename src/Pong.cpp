#include <print.h>
#include "pong.h"
#include <stdlib.h>
#include <math.h>
#include <numbers>

constexpr double pi = std::numbers::pi;
Pong::Pong(const char* name, int width, int height) : Game(name, width, height)
{
    SDL_Init(SDL_INIT_EVERYTHING);

    ball_x = width / 2;
    ball_y = height / 2;

    constexpr int ball_speed = 100;
    int angle = rand() % 360 * pi / 2;
    ball_speed_x = cos(angle) * ball_speed;
    ball_speed_y = sin(angle) * ball_speed;

    l_paddle_x = 10;
    r_paddle_x = width - 10 - paddle_w;
    r_paddle_y = l_paddle_y = height/2 - paddle_h / 2;
}



void  Pong::update() 
{
    print("Pong update\n");

    //move ball
    const float new_ball_x = ball_x + ball_speed_x *deltaTime;
    const float new_ball_y = ball_y + ball_speed_y *deltaTime;
    vprint(ball_speed_x);
    vprint(ball_speed_x * deltaTime);
    vprint(ball_speed_y);
    vprint(ball_speed_y * deltaTime);
    if (new_ball_x > width - hball_w || new_ball_x < hball_w)
        ball_speed_x *= -1;
    else
        ball_x = new_ball_x;
    if (new_ball_y > height - hball_h || new_ball_y < hball_h)
        ball_speed_y *= -1;
    else
        ball_y = new_ball_y;

    if (paddles_move_flags & l_paddle_up_mask)
    {
        const float new_l_paddle_y = l_paddle_y - paddle_speed * deltaTime;
        if (new_l_paddle_y > 0)
            l_paddle_y = new_l_paddle_y;
    }
    if (paddles_move_flags & l_paddle_down_mask)
    {
        const float new_l_paddle_y = l_paddle_y + paddle_speed * deltaTime;
        if (new_l_paddle_y < height - paddle_h)
            l_paddle_y = new_l_paddle_y;
    }
    if (paddles_move_flags & r_paddle_up_mask)
    {
        const float new_r_paddle_y = r_paddle_y - paddle_speed * deltaTime;
        if (new_r_paddle_y > 0)
            r_paddle_y = new_r_paddle_y;
    }
    if (paddles_move_flags & r_paddle_down_mask)
    {
        const float new_r_paddle_y = r_paddle_y + paddle_speed * deltaTime;
        if (new_r_paddle_y < height - paddle_h)
            r_paddle_y = new_r_paddle_y;
        vprint(new_r_paddle_y);
        vprint(r_paddle_y);
    }

    //reset flags
    paddles_move_flags = 0;
}
void Pong::render()
{
    print("Pong render\n");

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    //render ball
    SDL_Rect ball_rect = SDL_Rect();
    ball_rect.w = ball_w;
    ball_rect.h = ball_h;
    ball_rect.x = ball_x;
    ball_rect.y = ball_y;
    SDL_RenderDrawRect(renderer, &ball_rect);

    //draw left paddle
    SDL_Rect l_paddle_rect = SDL_Rect();
    l_paddle_rect.w = paddle_w;
    l_paddle_rect.h = paddle_h;
    l_paddle_rect.x = l_paddle_x;
    l_paddle_rect.y = l_paddle_y;
    SDL_RenderDrawRect(renderer, &l_paddle_rect);

    //draw left paddle
    SDL_Rect r_paddle_rect = SDL_Rect();
    r_paddle_rect.w = paddle_w;
    r_paddle_rect.h = paddle_h;
    r_paddle_rect.x = r_paddle_x;
    r_paddle_rect.y = r_paddle_y;
    SDL_RenderDrawRect(renderer, &r_paddle_rect);

    SDL_RenderPresent(renderer);
}
void Pong::handleEvents() 
{
    print("Pong events\n");
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0)
    {
        switch (event.type) 
        {
        case SDL_QUIT:
            stateFlags = 0;
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_w:
                paddles_move_flags |= l_paddle_up_mask;
                break;
            case SDLK_s:
                paddles_move_flags |= l_paddle_down_mask;
                break;
            case SDLK_UP:
                paddles_move_flags |= r_paddle_up_mask;
                break;
            case SDLK_DOWN:
                paddles_move_flags |= r_paddle_down_mask;
                break;
            }
            break;
        }
    }
}

