#pragma once
#include "Core/GameObject.h"
#include "Game/Components.h"

class HealthBar : public GameObject
{
public:
	HealthBar( SDL_Renderer* renderer, World* world, EntityId newParentId, int health );
private:
	Follow* target;
	Position* position;
	Health* hp;
};