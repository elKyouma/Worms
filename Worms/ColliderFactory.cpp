#include "ColliderFactory.h"

void ColliderFactory::Init( b2World* physicsWorld )
{
	this->physicsWorld = physicsWorld;
}
