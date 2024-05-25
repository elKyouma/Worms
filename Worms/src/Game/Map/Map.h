#pragma once
#include <SDL2/SDL.h>
#include "ECS/World.h"
#include "Core/Utils.h"
class Map
{
public:
	Map( SDL_Renderer* renderer, World* world, b2World* physicsWorld );
	~Map();

	void Update( SDL_Renderer* renderer );
private:
	EntityId mapId;
	World* world;
	Position* pos;
	std::optional<PhysicTexture> physTex;
};

