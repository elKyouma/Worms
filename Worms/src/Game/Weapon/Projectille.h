#pragma once
#include <memory>
#include "Core/GameObject.h"
#include "Core/Physics/Collider.h"
#include "Game/Components.h"
#include "Game/Systems.h"

class Projectille : public GameObject
{
public:
	Projectille( SDL_Renderer* newRenderer, World* newWorld );
	void Initialise( float posX, float posY, float vX, float vY );
	~Projectille();
	void Update();
private:

	void onCollision( b2Contact* constact );

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
};

