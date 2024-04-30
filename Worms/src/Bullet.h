#pragma once
#include "ECS/Components.h"
#include "ECS/Systems.h"
#include "ECS/World.h"



class Bullet
{
public:
	Bullet(SDL_Renderer* renderer, World* world, b2World* physicsWorld);
	~Bullet();
	void Update();
private:
	EntityId bulletId;
	RigidBody* rigidBody;
	World* world;
};

