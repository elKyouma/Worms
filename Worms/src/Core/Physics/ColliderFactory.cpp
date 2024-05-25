#include "ColliderFactory.h"
#include "Game/Components.h"

void ColliderFactory::Init( b2World* physicsWorld )
{
	this->physicsWorld = physicsWorld;
}

Collider ColliderFactory::CreateTrigger( b2Shape* shape, b2Vec2 position, PhysicsInfo info, Position* parent )
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_kinematicBody;
	bodyDef.fixedRotation = true;
	b2Body* body = physicsWorld->CreateBody( &bodyDef );

	b2FixtureDef fixtureDef;
	fixtureDef.isSensor = true;
	fixtureDef.shape = shape;
	fixtureDef.friction = 1;
	fixtureDef.density = 1;
	fixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(&info);
	body->CreateFixture( &fixtureDef );

	return Collider( body, position, parent );
}

Collider ColliderFactory::CreateDynamic( b2Shape* shape, b2Vec2 position, PhysicsInfo info, Position* parent )
{
	static b2BodyDef bodyDef;
	bodyDef.position = position;
	bodyDef.type = b2_dynamicBody;
	bodyDef.angularDamping = 1.0f;
	b2Body* body = physicsWorld->CreateBody( &bodyDef );

	static b2FixtureDef fixtureDef;
	fixtureDef.shape = shape;
	fixtureDef.friction = 1;
	fixtureDef.density = 1;
	fixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(&info);
	body->CreateFixture( &fixtureDef );

	return std::move( Collider( body, position, parent ) );
}

Collider ColliderFactory::CreateKinetic( b2Shape* shape, b2Vec2 position, PhysicsInfo info, Position* parent )
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_kinematicBody;
	bodyDef.fixedRotation = true;
	b2Body* body = physicsWorld->CreateBody( &bodyDef );

	b2FixtureDef fixtureDef;
	fixtureDef.shape = shape;
	fixtureDef.friction = 1;
	fixtureDef.density = 1;
	fixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(&info);
	body->CreateFixture( &fixtureDef );

	return Collider( body, position, parent );
}

Collider ColliderFactory::CreateStatic( b2Shape* shape, b2Vec2 position, PhysicsInfo info )
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.fixedRotation = true;
	bodyDef.position = position;
	b2Body* body = physicsWorld->CreateBody( &bodyDef );

	b2FixtureDef fixtureDef;
	fixtureDef.shape = shape;
	fixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(&info);
	body->CreateFixture( &fixtureDef );

	return Collider( body, position );
}
