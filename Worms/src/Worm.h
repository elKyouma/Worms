#pragma once
#include <box2d/b2_world.h>

#include "ECS/Components.h"
#include "ECS/Systems.h"
#include "ECS/World.h"
#include "Tags.h"

class Worm
{
public:
	Worm( SDL_Renderer* renderer, World* world, b2World* physicsWorld );
	~Worm();
	void Update();
	void Activate();
	void Disactivate();
private:
	EntityId wormId;
	RigidBody* rb;
	Position* pos;
	World* world;

	PhysicsInfo physicsInfo;

	static constexpr float WORM_SPEED = 5.f;
	void First( b2Contact* contact );
	void Second( b2Contact* contact );
};

