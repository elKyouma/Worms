#pragma once
#include "ComponentManager.h"
#include "EntityManager.h"
#include "SystemManager.h"

class World
{
public:
	World();
	EntityId CreateEntity();
	void DestroyEntity( EntityId ent );

	EntityId CopyEntity( EntityId toCopy );

	template<typename Component>
	Component& AddComponent( EntityId ent );
	template<typename Component>
	Component& GetComponent( EntityId ent );
	template<typename Component>
	Component RemoveComponent( EntityId ent );


	void Update();
private:
	EntityManager entManager{};
	ComponentManager comManager{};
	SystemManager sysManager{ comManager };
};

template<typename Component>
Component& World::AddComponent( EntityId ent )
{
	Signature newSign = entManager.AddToSignature( ent, comManager.GetComponentId<Component>() );
	sysManager.OnSignatureChange( ent, newSign );
	return comManager.AddComponent<Component>( ent );
}

template<typename Component>
Component& World::GetComponent( EntityId ent )
{
	return comManager.GetComponent<Component>( ent );
}

template<typename Component>
Component World::RemoveComponent( EntityId ent )
{
	Signature newSign = entManager.DeleteFromSignature( ent, comManager.GetComponentId<Component>() );
	sysManager.OnSignatureChange( ent, newSign );
	return comManager.RemoveComponent<Component>( ent );
}
