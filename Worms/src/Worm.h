#pragma once
#include <box2d/b2_world.h>

#include "ECS/Components.h"
#include "ECS/Systems.h"
#include "ECS/World.h"

class Worm
{
public:
	Worm( SDL_Renderer* renderer, World* world, b2World* physicsWorld );
	~Worm();
	void Update();

private:
	EntityId wormId;
	RigidBody* rb;
	Position* pos;
	World* world;

	static constexpr float WORM_SPEED = 2.f;
};

