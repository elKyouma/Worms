#pragma once
#include <array>
#include <unordered_map>
#include "ECS_Types.h"

class IComponentArray
{

};

template<typename Data>
class ComponentArray : IComponentArray
{
public:
	Data AddData( Entity ent );
	Data& GetData( Entity ent );
	void SetData( Entity ent, Data& data );
	void EraseData( Entity ent );

	ComponentType GetType;
private:
	ComponentType typeId;

	std::array<Data, MAX_COMPONENTS> components;
	std::unordered_map<Entity, Entity> entityToIndex;
	std::unordered_map<Entity, Entity> indexToEntity;

	uint8_t amountOfComponents = 0;
};

template<typename Data>
inline Data ComponentArray<Data>::AddData( Entity ent )
{
	entityToIndex[ent] = amountOfComponents;
	indexToEntity[amountOfComponents] = ent;

	return components[amountOfComponents++];
}

template<typename Data>
inline Data& ComponentArray<Data>::GetData( Entity ent )
{
	return components[ent];
}

template<typename Data>
inline void ComponentArray<Data>::SetData( Entity ent, Data& data )
{
	components[ent] = data;
}

template<typename Data>
inline void ComponentArray<Data>::EraseData( Entity ent )
{
	Entity index = entityToIndex[ent];
	entityToIndex.erase( ent );

	components[index] = components[amountOfComponents];
	indexToEntity[index] = components[amountOfComponents];
	indexToEntity.erase( amountOfComponents );

	amountOfComponents--;
}
