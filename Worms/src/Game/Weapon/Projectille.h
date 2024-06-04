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
	Projectille( float posX, float posY, float vX, float vY, float offset = 0 );
	void Initialise( SDL_Renderer* newRenderer, World* newWorld );
	void Update();
	void CleanUp();
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
};

