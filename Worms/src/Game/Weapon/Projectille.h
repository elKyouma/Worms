#pragma once
#include <memory>
#include "Core/GameObject.h"
#include "Core/Physics/Collider.h"
#include "Game/Components.h"
#include "Game/Systems.h"

class Projectille : public GameObject
{
public:
	Projectille( SDL_Renderer* newRenderer, World* newWorld, b2World* physicsWorld );
	~Projectille();
	void Update();
private:
	RigidBody* rigidBody;
	Position* position;
	Rotation* rotation;
	std::unique_ptr<Collider> collider;
};

