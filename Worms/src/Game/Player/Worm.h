#pragma once
#include <box2d/b2_world.h>
#include <memory>
#include "Core/GameObject.h"
#include "Core/Physics/Collider.h"
#include "Core/Physics/ColliderFactory.h"
#include "Game/Components.h"
#include "Game/Player/HealthBar.h"
#include "Game/Systems.h"
#include "Game/Tags.h"

class Worm : public GameObject
{
public:
	Worm( SDL_Renderer* newRenderer, World* newWorld, b2World* physicsWorld, const Camera& camera, SDL_Texture* texture );
	void Update() override;
	void CleanUp() override;
	void Render() override;

	void Activate();
	void Disactivate();
	bool IsGrounded() const;

private:
	RigidBody* rb;
	Position* pos;
	std::unique_ptr<HealthBar> healthBar;
	std::unique_ptr<Collider> collider = NULL;

	bool grounded = false;
	bool active = false;

	PhysicsInfo physicsInfo;
	PhysicsInfo groundedPhysicsInfo;

	static constexpr float WORM_SPEED = 2.f;
	static constexpr float JUMP_FORCE = 2.5f;
};

