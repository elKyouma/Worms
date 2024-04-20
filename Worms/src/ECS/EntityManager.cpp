#include "EntityManager.h"

EntityManager::EntityManager()
{
	for ( Entity e = 0u; e < MAX_ENTITIES; e++ )
		availableEntities.emplace( e );
}

Entity EntityManager::CreateEntity()
{
	Entity newEntity = availableEntities.front();
	availableEntities.pop();
	return newEntity;
}

void EntityManager::DestroyEntity( Entity ent )
{
	availableEntities.push( ent );
}

void EntityManager::SetSignature( Entity ent, Signature signature )
{
	entities[ent] = signature;
}

Signature EntityManager::GetSignature( Entity ent )
{
	return entities[ent];
}
