#pragma once
#include "ECS/Components.h"
#include "ECS/World.h"

class Weapon
{
public:
	Weapon( SDL_Renderer* renderer, World* world, EntityId parentId );
	~Weapon();
	void Update();
	void Use();

private:
	EntityId weaponId;
	EntityId parentId;
	Position* pos;
	Rotation* rot;
	World* world;
};

