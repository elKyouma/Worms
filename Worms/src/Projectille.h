#pragma once
#include "GameObject.h"
#include "ECS/Components.h"
#include "ECS/Systems.h"



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
};

