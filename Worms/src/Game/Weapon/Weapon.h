#pragma once
#include <vector>
#include "Core/Camera.h"
#include "Core/GameObject.h"
#include "Game/Components.h"
#include "Game/Weapon/Projectile.h"
#include "WeaponImpl.h"

class Weapon : public GameObject
{
public:
	Weapon( const Camera& camera );

	void Initialise( SDL_Renderer* newRenderer, World* newWorld ) override;
	void Update() override;
	void Render() override;
	void SetParent( EntityId newParent ) { parentId = newParent; }
	void SetParams( WeaponImpl params ) { weaponParams = params; }
	void SetTexture( SDL_Texture* texture ) { world->GetComponent<Sprite>( objectId ).texture = texture; }
	void SetExplosionSound( Sound* sound ) { explosionSound = sound; }
	void SetCollisionSound( Sound* sound ) { collisionSound = sound; }
	void SetShootingSound( Sound* sound ) { shootingSound = sound; }
	void SetProjectileTexture( SDL_Texture* texture ) { projTexture = texture; }

private:
	EntityId parentId;
	Position* pos;
	Rotation* rot;
	float force = 0;
	SDL_Texture* powerBar;
	SDL_Texture* projTexture;
	Sound* explosionSound;
	Sound* collisionSound;
	Sound* shootingSound;

	const Camera& camera;
	WeaponImpl weaponParams;
};

