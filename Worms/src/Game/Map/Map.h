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
	SDL_Point GlobalToLocalPos( const Position& mapPos );
	void SDL_Surface( SDL_Point point );
private:
	void DestroyMap( b2Contact* contact );
	float Distance( const float x1, const float y1, const float x2, const float y2 );

	void CreateNewColliders();

	bool destroyed = false;
	SDL_Renderer* renderer;
	b2World* physicsWorld;
	World* world;

	EntityId mapId;
	Position* pos;
	Sprite* sprite;
	Position bulltetPos;
	PhysicsInfo physicsInfo;
	std::optional<PhysicTexture> physTex;

	SDL_Point mapSize{};
};

