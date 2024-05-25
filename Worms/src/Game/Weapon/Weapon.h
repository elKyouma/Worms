#pragma once
#include "Core/GameObject.h"
#include "Game/Components.h"
class Weapon : public GameObject
{
public:
	Weapon( SDL_Renderer* newRenderer, World* newWorld );
	~Weapon();
	void Update();
	void Use();
	void SetParent( EntityId newParent ) { parentId = newParent; }

private:
	EntityId parentId;
	Position* pos;
	Rotation* rot;
};

