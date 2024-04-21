#include "EntityManager.h"

EntityManager::EntityManager()
{
	for ( EntityId e = 0u; e < MAX_ENTITIES; e++ )
		availableEntities.emplace( e );
}

EntityId EntityManager::CreateEntity()
{
	EntityId newEntity = availableEntities.front();
	availableEntities.pop();
	return newEntity;
}

void EntityManager::DestroyEntity( EntityId ent )
{
	availableEntities.push( ent );
}

void EntityManager::SetSignature( EntityId ent, Signature signature )
{
	entities[ent] = signature;
}

Signature EntityManager::GetSignature( EntityId ent )
{
	return entities[ent];
}

uint16_t EntityManager::GetAmountOfAvailableEntities() const
{
	return availableEntities.size();
}
