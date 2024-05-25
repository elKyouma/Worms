#pragma once
#include <vector>
#include "Core/GameObject.h"
#include "Game/Components.h"
#include "Game/Weapon/Projectille.h"

class Weapon : public GameObject
{
public:
	Weapon( SDL_Renderer* newRenderer, World* newWorld );
	~Weapon();
	void Update();
	void SetParent( EntityId newParent ) { parentId = newParent; }

private:
	EntityId parentId;
	Position* pos;
	Rotation* rot;
	std::vector<Projectille> projectilles;
	float force = 0;
};

