#pragma once
#include "Core/GameObject.h"
#include "Core/Camera.h"
#include "Game/Components.h"

class HealthBar : public GameObject
{
public:
	HealthBar( SDL_Renderer* renderer, World* world, EntityId newParentId, Camera camera, int health );
	void Render() override;
private:
	Follow* target;
	Position* position;
	Health* hp;
	SDL_Texture* healthBar;
	const Camera& camera;
};