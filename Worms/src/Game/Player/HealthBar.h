#pragma once
#include "Core/GameObject.h"
#include "Core/Camera/Camera.h"
#include "Game/Components.h"

class HealthBar : public GameObject
{
public:
	HealthBar( SDL_Renderer* renderer, World* world, EntityId newParentId, const Camera& camera, int health, SDL_Texture* texture );
	void Render() override;
private:
	Follow* target;
	Position* position;
	Health* hp;
	SDL_Texture* healthBar;
	const Camera& camera;
};