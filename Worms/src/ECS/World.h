#pragma once
#include "ComponentManager.h"
#include "EntityManager.h"
#include "SystemManager.h"

class World
{
public:
	World();
	EntityId CreateEntity();
	void DestroyEntity( const EntityId ent );

	EntityId CopyEntity( const EntityId toCopy );

	template<typename Component>
	Component& AddComponent( const EntityId ent );
	template<typename Component>
	Component& GetComponent( const EntityId ent );
	template<typename Component>
	Component RemoveComponent( const EntityId ent );


	void Update();
private:
	EntityManager entManager{};
	ComponentManager comManager{};
	SystemManager sysManager{ comManager };
};

template<typename Component>
Component& World::AddComponent( const EntityId ent )
{
	Signature newSign = entManager.AddToSignature( ent, comManager.GetComponentId<Component>() );
	sysManager.OnSignatureChange( ent, newSign );
	return comManager.AddComponent<Component>( ent );
}

template<typename Component>
Component& World::GetComponent( const EntityId ent )
{
	return comManager.GetComponent<Component>( ent );
}

template<typename Component>
Component World::RemoveComponent( const EntityId ent )
{
	Signature newSign = entManager.DeleteFromSignature( ent, comManager.GetComponentId<Component>() );
	sysManager.OnSignatureChange( ent, newSign );
	return comManager.RemoveComponent<Component>( ent );
}
