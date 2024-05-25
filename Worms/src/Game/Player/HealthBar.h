#pragma once
#include "Core/GameObject.h"
#include "Game/Components.h"

class HealthBar : GameObject
{
public:
	HealthBar( SDL_Renderer* renderer, World* world, EntityId newParentId, int health );
	void Update();
private:
	EntityId parentId;
	Position* position;
	Health* hp;
};