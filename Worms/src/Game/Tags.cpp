#include "Tags.h"

std::optional<EntityId> GetEntityWithTag( b2Contact* contact, PhysicsTag tag )
{
	if ( reinterpret_cast<PhysicsInfo*>(contact->GetFixtureA()->GetUserData().pointer)->tag == tag )
		return reinterpret_cast<PhysicsInfo*>(contact->GetFixtureA()->GetUserData().pointer)->id;
	else if ( reinterpret_cast<PhysicsInfo*>(contact->GetFixtureB()->GetUserData().pointer)->tag == tag )
		return reinterpret_cast<PhysicsInfo*>(contact->GetFixtureB()->GetUserData().pointer)->id;
	else
		return {};
}