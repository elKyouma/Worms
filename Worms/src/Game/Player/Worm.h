#pragma once
#include <box2d/b2_world.h>
#include "Core/GameObject.h"
#include "Game/Components.h"
#include "Game/Systems.h"
#include "Game/Tags.h"

class Worm : public GameObject
{
public:
	Worm( SDL_Renderer* newRenderer, World* newWorld, b2World* physicsWorld );
	~Worm();
	void Update();
	void Activate();
	void Disactivate();
	bool IsGrounded() const;

private:
	RigidBody* rb;
	Position* pos;

	bool grounded = false;
	bool active = false;

	PhysicsInfo physicsInfo;

	static constexpr float WORM_SPEED = 3.f;
	static constexpr float JUMP_FORCE = 2.5f;
};

