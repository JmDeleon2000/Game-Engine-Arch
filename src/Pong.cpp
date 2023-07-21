#include <print.h>
#include "pong.h"
#include <stdlib.h>
#include <math.h>
#include <numbers>
#include <time.h>

static void reset_ball(float* ball_speed_x, float* ball_speed_y, 
                        float* ball_x, float* ball_y,
                        int w, int h)
{
    constexpr double pi = std::numbers::pi;
    constexpr float ball_speed = 500;

    const float angles[] = {pi/3*4, pi / 3 * 8};
    int angle_index = rand() % 2;
    *ball_speed_x = ball_speed * cos(angles[angle_index]);
    *ball_speed_y = ball_speed * sin(angles[angle_index]);


    *ball_x = w / 2;
    *ball_y = h / 2;
}


Pong::Pong(const char* name, int width, int height) : Game(name, width, height)
{
    srand(time(NULL));
    SDL_Init(SDL_INIT_EVERYTHING);

    reset_ball(&ball_speed_x, &ball_speed_y,
                &ball_x, &ball_y,
                width, height);

    l_paddle_x = 10;
    r_paddle_x = width - 10 - paddle_w;
    r_paddle_y = l_paddle_y = height/2 - paddle_h / 2;
}



void  Pong::update() 
{
    print("Pong update\n");

    if (paddles_move_flags & l_paddle_up_mask)
    {
        const float new_l_paddle_y = l_paddle_y - paddle_speed * deltaTime;
        if (new_l_paddle_y > 0)
            l_paddle_y = new_l_paddle_y;
        else
            l_paddle_y = 0;
    }
    if (paddles_move_flags & l_paddle_down_mask)
    {
        const float new_l_paddle_y = l_paddle_y + paddle_speed * deltaTime;
        if (new_l_paddle_y < height - paddle_h)
            l_paddle_y = new_l_paddle_y;
        else
            l_paddle_y = height - paddle_h;
    }
    if (paddles_move_flags & r_paddle_up_mask)
    {
        const float new_r_paddle_y = r_paddle_y - paddle_speed * deltaTime;
        if (new_r_paddle_y > 0)
            r_paddle_y = new_r_paddle_y;
        else
            r_paddle_y = 0;
    }
    if (paddles_move_flags & r_paddle_down_mask)
    {
        const float new_r_paddle_y = r_paddle_y + paddle_speed * deltaTime;
        if (new_r_paddle_y < height - paddle_h)
            r_paddle_y = new_r_paddle_y;
        else
            r_paddle_y = height - paddle_h;
    }

    //reset flags
    paddles_move_flags = 0;



    //move ball
    const float new_ball_x = ball_x + ball_speed_x * deltaTime;
    const float new_ball_y = ball_y + ball_speed_y * deltaTime;

    if (new_ball_x < l_paddle_x + paddle_w 
            && (new_ball_y < l_paddle_y + paddle_h && new_ball_y > l_paddle_y)
        || new_ball_x > r_paddle_x - ball_w 
            && (new_ball_y < r_paddle_y + paddle_h && new_ball_y > r_paddle_y)
        )
        ball_speed_x *= -1;
    else
    {
        ball_x = new_ball_x;
        if (new_ball_x > width - hball_w)
        {
            reset_ball(&ball_speed_x, &ball_speed_y,
                &ball_x, &ball_y,
                width, height);
            l_player_score++;
        }
        if (new_ball_x < 0)
        {
            reset_ball(&ball_speed_x, &ball_speed_y,
                &ball_x, &ball_y,
                width, height);
            r_player_score++;
        }
    }
    if (new_ball_y > height - ball_h || new_ball_y < 0)
        ball_speed_y *= -1;
    else
        ball_y = new_ball_y;
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

