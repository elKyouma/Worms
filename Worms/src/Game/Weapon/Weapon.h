#pragma once
#include <vector>
#include "Core/Camera.h"
#include "Core/GameObject.h"
#include "Game/Components.h"
#include "Game/Weapon/Projectille.h"

class Weapon : public GameObject
{
public:
	Weapon( const Camera& camera );
	~Weapon();

	void Initialise( SDL_Renderer* newRenderer, World* newWorld ) override;
	void Update() override;
	void Render() override;
	void SetParent( EntityId newParent ) { parentId = newParent; }

private:
	EntityId parentId;
	Position* pos;
	Rotation* rot;
	float force = 0;
	SDL_Texture* powerBar;
	const Camera& camera;
};

