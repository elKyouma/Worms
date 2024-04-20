#pragma once
#include <array>
#include <bitset>
#include <queue>
#include "ECS_Types.h"

class EntityManager
{
public:
	EntityManager();

	Entity CreateEntity();
	void DestroyEntity( Entity ent );

	void SetSignature( Entity ent, Signature signature );
	Signature GetSignature( Entity ent );

private:
	std::queue<Entity> availableEntities;
	std::array<Signature, MAX_ENTITIES> entities;

};

