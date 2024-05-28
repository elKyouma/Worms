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

	Collider CreateTriggerBody( b2Shape* shape, b2Vec2 position, const PhysicsInfo& info = {} );
	Collider CreateDynamicBody( b2Shape* shape, b2Vec2 position, const PhysicsInfo& info = {} );
	Collider CreateKineticBody( b2Shape* shape, b2Vec2 position, const PhysicsInfo& info = {} );
	Collider CreateStaticBody( b2Shape* shape, b2Vec2 position, const PhysicsInfo& info = {} );

	void CreateTriggerFixture( b2Body* body, b2Shape* shape, const PhysicsInfo& info = {} );
	void CreateDynamicFixture( b2Body* body, b2Shape* shape, const PhysicsInfo& info = {} );
	void CreateKineticFixture( b2Body* shape, b2Shape* body, const PhysicsInfo& info = {} );
	void CreateStaticFixture( b2Body* body, b2Shape* shape, const PhysicsInfo& info = {} );

	b2World* GetPhysicsWorld() { return physicsWorld; };

private:
	ColliderFactory() = default;

	b2World* physicsWorld;
};

