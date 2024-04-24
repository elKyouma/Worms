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

void EntityManager::DestroyEntity( const EntityId ent )
{
	availableEntities.push( ent );
}

Signature EntityManager::AddToSignature( const EntityId ent, const ComponentType type )
{
	return signatures[ent].set( type, true );
}

Signature EntityManager::DeleteFromSignature( const EntityId ent, const ComponentType type )
{
	return signatures[ent].set( type, false );
}

void EntityManager::SetSignature( const EntityId ent, const Signature signature )
{
	signatures[ent] = signature;
}

Signature EntityManager::GetSignature( const EntityId ent )
{
	return signatures[ent];
}

uint16_t EntityManager::GetAmountOfAvailableEntities() const
{
	return availableEntities.size();
}
