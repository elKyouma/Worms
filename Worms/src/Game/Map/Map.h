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
	void DestroyMap( b2Contact* contact );
	float Distance( const float x1, const float y1, const float x2, const float y2 );

	bool destroyed = false;
	SDL_Renderer* renderer;
	EntityId mapId;
	Position bulltetPos;

	World* world;
	b2World* physicsWorld;
	Position* pos;
	PhysicsInfo physicsInfo;
	std::optional<PhysicTexture> physTex;
};

