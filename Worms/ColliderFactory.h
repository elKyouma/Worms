#pragma once
#include "box2d/b2_world.h"

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

	void CreateTrigger();
	void CreateDynamic();
	void CreateKinetic();
	void CreateStatic();

private:
	ColliderFactory();

	b2World* physicsWorld
};

