#pragma once
#include "Core/GameObject.h"
#include "Game/Components.h"
class Weapon : public GameObject
{
public:
	Weapon( SDL_Renderer* newRenderer, World* newWorld, EntityId parentId );
	~Weapon();
	void Update();
	void Use();

private:
	EntityId parentId;
	Position* pos;
	Rotation* rot;
};

