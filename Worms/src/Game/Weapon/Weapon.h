#pragma once
#include <vector>
#include "Core/GameObject.h"
#include "Game/Components.h"
#include "Game/Weapon/Projectille.h"
#include "Core/Camera.h"

class Weapon : public GameObject
{
public:
	Weapon( SDL_Renderer* newRenderer, World* newWorld, Camera &camera );
	~Weapon();
	void Update();
	void Render();
	void SetParent( EntityId newParent ) { parentId = newParent; }

private:
	EntityId parentId;
	Position* pos;
	Rotation* rot;
	std::vector<std::unique_ptr<Projectille>> projectilles;
	float force = 0;
	SDL_Texture *powerBar;
	Camera &camera;
};

