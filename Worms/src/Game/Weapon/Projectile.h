#pragma once
#include <memory>
#include <SDL2/SDL.h>
#include "Core/Audio/Sound.h"
#include "Core/GameObject.h"
#include "Core/Physics/Collider.h"
#include "Core/Time.h"
#include "Game/Components.h"
#include "Game/Systems.h"

class Projectile : public GameObject
{
public:
	Projectile( float posX, float posY, float vX, float vY );
	void Initialise( SDL_Renderer* newRenderer, World* newWorld ) override;
	void Update() override;
	void CleanUp() override;

	void SetExplosionOffset( float time ) { params.explosionOffset = time; }
	void SetTexture( SDL_Texture* texture ) { this->texture = texture; }
	void SetExplosionSound( Sound* sound ) { explosionSound = sound; }
	void SetCollisionSound( Sound* sound ) { collisionSound = sound; }
	void SetExplosionRadius( float radius ) { params.explosionRadius = radius; }
	void SetBaseDamage( float damage ) { params.baseDamage = damage; }
	void SetGravityScale( float scale ) { params.gravityScale = scale; }
	void SetMaxSpeed( float speed ) { params.maxSpeed = speed / 10.f; }
	void SetCamera( Camera* camera ) { this->camera = camera; }

private:

	void onCollision( b2Contact* constact );

	float startPosX, startPosY, startVelX, startVelY;

	bool createSensor = false;
	PhysicsInfo physicsInfo;
	PhysicsInfo sensorInfo;
	b2Fixture* fixture;
	Camera* camera;
	std::unique_ptr<Collider> collider;
	Time::Timer timer;
	Parameters params{};

	SDL_Texture* texture;
	Sound* explosionSound;
	Sound* collisionSound;
};

