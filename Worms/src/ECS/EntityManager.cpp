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

Signature EntityManager::AddToSignature( EntityId ent, ComponentType type )
{
	return signatures[ent].set( type - 1, true );
}

Signature EntityManager::DeleteFromSignature( EntityId ent, ComponentType type )
{
	return signatures[ent].set( type - 1, false );
}

void EntityManager::SetSignature( EntityId ent, Signature signature )
{
	signatures[ent] = signature;
}

Signature EntityManager::GetSignature( EntityId ent )
{
	return signatures[ent];
}

uint16_t EntityManager::GetAmountOfAvailableEntities() const
{
	return availableEntities.size();
}
