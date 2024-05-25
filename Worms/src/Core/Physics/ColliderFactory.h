#pragma once
#include <box2d/b2_shape.h>
#include <box2d/b2_world.h>
#include "Core/Physics/Collider.h"
#include "Game/Tags.h"

class ColliderFactory
{
public:
	ColliderFactory( const ColliderFactory& ) = delete;
	ColliderFactory( ColliderFactory&& ) = delete;

	void Init( b2World* physicsWorld );

	static ColliderFactory& Get()
	{
		static ColliderFactory factory{};
		return factory;
	}

	Collider CreateTrigger( b2Shape* shape, b2Vec2 position, PhysicsInfo info = {}, Position* parent = NULL );
	Collider CreateDynamic( b2Shape* shape, b2Vec2 position, PhysicsInfo info = {}, Position* parent = NULL );
	Collider CreateKinetic( b2Shape* shape, b2Vec2 position, PhysicsInfo info = {}, Position* parent = NULL );
	Collider CreateStatic( b2Shape* shape, b2Vec2 position, PhysicsInfo info = {} );

private:
	ColliderFactory() = default;

	b2World* physicsWorld;
};

