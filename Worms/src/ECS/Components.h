#pragma once
#include "SDL2/SDL.h"

struct Position
{
	float x = 0.f, y = 0.f;
};

struct Motion
{
	float v_x = 0.f, v_y = 0.f;
};

struct Sprite
{
	SDL_Texture* texture;
};