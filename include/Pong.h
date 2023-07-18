#pragma once
#include "game.h"


class Pong : Game
{
	Pong(const char* name, int width, int height);

	void update() override;
	void render() override;
	void handleEvents() override;
};