#pragma once
#include <memory>
#include "Core/GameObject.h"
#include "Core/Physics/Collider.h"
#include "Game/Components.h"
#include "Game/Systems.h"
#include "Core/Time.h"

class Projectille : public GameObject
{
public:
	Projectille( float posX, float posY, float vX, float vY);
	void Initialise( SDL_Renderer* newRenderer, World* newWorld );
	void Update();
	void CleanUp();

	void SetExplosionOffset( float time ) { explosionOffset = time; }
	void SetTexture( std::string path ) { texturePath = path; }
	void SetExplosionRadius( float radius ) { explosionRadius = radius; }
	void SetBaseDamage( float damage ) { baseDamage = damage; }
	void SetGravityScale( float scale ) { gravityScale = scale; }
	void SetMaxSpeed( float speed ) { maxSpeed = speed / 10.f; }
	
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

	float explosionOffset = 0;
	std::string texturePath = "placeHolderBullet.png";
	float explosionRadius = 1.f;
	float baseDamage = 40.f;
	float gravityScale = 1.f;
	float maxSpeed = 0.25f;
};

