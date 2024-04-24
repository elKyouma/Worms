#include "Components.h"
#include "Systems.h"
#include "World.h"

World::World()
{
	comManager.RegisterComponent<Position>();
	comManager.RegisterComponent<Motion>();
	sysManager.RegisterSystem<Movement>();
}

EntityId World::CreateEntity()
{
	return entManager.CreateEntity();
}

void World::DestroyEntity( const EntityId ent )
{
	comManager.RemoveAllComponents( ent, entManager.GetSignature( ent ) );
	entManager.DestroyEntity( ent );
	sysManager.UnsubscribeEntity( ent );
}

EntityId World::CopyEntity( const EntityId toCopy )
{
	EntityId newId = entManager.CreateEntity();
	Signature toCopySign = entManager.GetSignature( toCopy );
	entManager.SetSignature( newId, toCopySign );
	comManager.AddComponents( newId, toCopySign );
	sysManager.OnSignatureChange( newId, toCopySign ); // Maybe could be optimised
	return newId;
}

void World::Update()
{
	sysManager.Update();
}
