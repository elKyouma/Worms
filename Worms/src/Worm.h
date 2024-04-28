#pragma once
#include "ECS/Components.h"
#include "ECS/Systems.h"
#include "ECS/World.h"

class Worm
{
public:
	Worm( SDL_Renderer* renderer, World* world );
	~Worm();
	void Update();
private:
	EntityId wormId;
	Motion* motion;
	SDL_Renderer* renderer;
	World* world;
};

