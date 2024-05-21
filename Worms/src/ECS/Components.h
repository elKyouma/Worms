#pragma once
#include <SDL2/SDL.h>
#include <box2d/b2_body.h>

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

struct RigidBody
{
	b2Body* body;
};

struct Rotation
{
	float degree;
};