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
	bool IsGrounded() const;

private:
	EntityId wormId;
	RigidBody* rb;
	Position* pos;
	World* world;

	bool grounded = false;
	bool active = false;

	PhysicsInfo physicsInfo;

	static constexpr float WORM_SPEED = 3.f;
	static constexpr float JUMP_FORCE = 2.5f;
};

