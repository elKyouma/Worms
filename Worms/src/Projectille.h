#pragma once
#include "ECS/Components.h"
#include "ECS/Systems.h"
#include "ECS/World.h"



class Projectille
{
public:
	Projectille(SDL_Renderer* renderer, World* world, b2World* physicsWorld);
	~Projectille();
	void Update();
private:
	EntityId projectilletId;
	RigidBody* rigidBody;
	Position* position;
	World* world;
};

