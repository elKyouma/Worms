#include "Tags.h"

std::optional<EntityId> GetEntityWithTag( b2Contact* contact, PhysicsTag tag )
{
	if ( reinterpret_cast<PhysicsInfo*>(contact->GetFixtureA()->GetUserData().pointer)->tag == PhysicsTag::BULLET )
		return reinterpret_cast<PhysicsInfo*>(contact->GetFixtureA()->GetUserData().pointer)->id;
	else if ( reinterpret_cast<PhysicsInfo*>(contact->GetFixtureB()->GetUserData().pointer)->tag == PhysicsTag::BULLET )
		return reinterpret_cast<PhysicsInfo*>(contact->GetFixtureB()->GetUserData().pointer)->id;
	else
		return {};
}