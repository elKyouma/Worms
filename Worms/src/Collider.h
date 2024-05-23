#pragma once
#include <box2d/b2_contact.h>
#include <box2d/b2_fixture.h>
#include <functional>
#include "box2d/b2_world.h"
#include "ECS/Components.h"
#include "ECS/ECS_Types.h"
#include "Tags.h"

class Collider
{
public:
	Collider( b2World* physicsWorld, PhysicsInfo physicsInfo, b2Shape* shape, bool isTrigger = false );

	void SetParent( Position& pos, const b2Vec2 offset );
	void SetPosition( Position pos );

	void OnColliderEnter( std::function<void( b2Contact* )> callback );
	void OnCollider( std::function<void( b2Contact* )> callback );
	void OnColliderExit( std::function<void( b2Contact* )> callback );

	void Update();

private:
	PhysicsInfo physicsInfo;
	b2Body* body;
	b2BodyDef bodyDef;
	b2FixtureDef fixtureDef;
	Position* parent = NULL;

	b2Vec2 offset;
	Position pos;
};

