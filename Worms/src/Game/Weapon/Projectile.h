#pragma once
#include <memory>
#include "Core/GameObject.h"
#include "Core/Physics/Collider.h"
#include "Core/Time.h"
#include "Game/Components.h"
#include "Game/Systems.h"

class Projectile : public GameObject
{
public:
	Projectile( float posX, float posY, float vX, float vY );
	void Initialise( SDL_Renderer* newRenderer, World* newWorld );
	void Update();
	void CleanUp();

	void SetExplosionOffset( float time ) { params.explosionOffset = time; }
	void SetTexture( std::string path ) { params.texturePath = path; }
	void SetExplosionRadius( float radius ) { params.explosionRadius = radius; }
	void SetBaseDamage( float damage ) { params.baseDamage = damage; }
	void SetGravityScale( float scale ) { params.gravityScale = scale; }
	void SetMaxSpeed( float speed ) { params.maxSpeed = speed / 10.f; }

private:

	void onCollision( b2Contact* constact );

	float startPosX, startPosY, startVelX, startVelY;

	bool destroyNextFrame = false;
	bool createSensor = false;
	PhysicsInfo physicsInfo;
	PhysicsInfo sensorInfo;
	RigidBody* rigidBody;
	Position* position;
	Rotation* rotation;
	b2Fixture* fixture;
	std::unique_ptr<Collider> collider;
	EntityId sensorId;
	Time::Timer timer;
	Parameters params{};
};
