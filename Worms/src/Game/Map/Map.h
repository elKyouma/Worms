#pragma once
#include <memory>
#include <SDL2/SDL.h>
#include "Core/Utils.h"
#include "ECS/World.h"
#include "Game/Components.h"
#include "Game/Tags.h"

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
	PhysicsInfo physicsInfo;
	std::optional<PhysicTexture> physTex;
};

