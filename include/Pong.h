#pragma once
#include "game.h"


class Pong : public Game
{
private:
	float ball_x;
	float ball_y;

	int ball_w = 20;
	int ball_h = 20;

	const int hball_h = ball_h / 2 + 1;
	const int hball_w = ball_w / 2 + 1;

	float ball_speed_x;
	float ball_speed_y;

	int paddle_w = 20;
	int paddle_h = 300;
	float l_paddle_x;
	float l_paddle_y;
	float r_paddle_x;
	float r_paddle_y;
	float paddle_speed = 1750.0f;

	int l_player_score = 0;
	int r_player_score = 0;

	const int hpaddle_h = paddle_h / 2 + 1;

	unsigned char paddles_move_flags;
	const unsigned char l_paddle_up_mask	=	0xC0;
	const unsigned char l_paddle_down_mask	=	0x30;
	const unsigned char r_paddle_up_mask	=	0x0C;
	const unsigned char r_paddle_down_mask	=	0x03;

public:
	Pong(const char* name, int width, int height);

	void update() override;
	void render() override;
	void handleEvents() override;
};