#pragma once
#include <SDL2/SDL.h>
#include "ECS/World.h"

class Map
{
public:
	Map( SDL_Renderer* renderer, World* world );
	~Map();
private:
	EntityId mapId;
	World* world;

};

