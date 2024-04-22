#pragma once
#include <array>
#include <bitset>
#include <queue>
#include "ECS_Types.h"

class EntityManager
{
public:
	EntityManager();

	EntityId CreateEntity();
	void DestroyEntity( EntityId ent );

	void AddToSignature( EntityId ent, ComponentType type );
	void DeleteFromSignature( EntityId ent, ComponentType type );
	void SetSignature( EntityId ent, Signature signature );
	Signature GetSignature( EntityId ent );

	uint16_t GetAmountOfAvailableEntities() const;

private:
	std::queue<EntityId> availableEntities;
	std::array<Signature, MAX_COMPONENTS> signatures;

};
