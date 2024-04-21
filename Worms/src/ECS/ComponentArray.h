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
	Data AddData( EntityId ent );
	Data& GetData( EntityId ent );
	Data& GetDataAtIndex( EntityId ent );
	void SetData( EntityId ent, Data data );
	void EraseData( EntityId ent );

	ComponentType GetType;
private:
	ComponentType typeId;

	std::array<Data, MAX_ENTITIES> components;
	std::unordered_map<EntityId, EntityId> entityToIndex;
	std::unordered_map<EntityId, EntityId> indexToEntity;

	uint8_t amountOfComponents = 0;
};

template<typename Data>
Data ComponentArray<Data>::AddData( EntityId ent )
{
	if ( amountOfComponents == MAX_ENTITIES )
		ECS_THROW( "Entities overflow" );

	entityToIndex[ent] = amountOfComponents;
	indexToEntity[amountOfComponents] = ent;

	return components[amountOfComponents++];
}

template<typename Data>
Data& ComponentArray<Data>::GetData( EntityId ent )
{
	auto it = entityToIndex.find( ent );
	if ( it == entityToIndex.end() )
		ECS_THROW( "You are trying to access component that doesn't exist" );
	EntityId index = it->second;
	return components[index];
}

template<typename Data>
inline Data& ComponentArray<Data>::GetDataAtIndex( EntityId index )
{
	if ( index >= amountOfComponents )
		ECS_THROW( "You are trying to access component by index that doesn't exist" );

	return components[index];
}

template<typename Data>
void ComponentArray<Data>::SetData( EntityId ent, Data data )
{
	auto it = entityToIndex.find( ent );
	if ( it == entityToIndex.end() )
		ECS_THROW( "You are trying to copy component to component that doesn't exist" );
	EntityId index = it->second;

	components[index] = data;
}

template<typename Data>
void ComponentArray<Data>::EraseData( EntityId ent )
{
	auto it = entityToIndex.find( ent );
	if ( it == entityToIndex.end() )
		ECS_THROW( "Component you are trying to erase doesn't exist" );

	EntityId index = it->second;

	amountOfComponents--;

	components[index] = components[amountOfComponents];
	components[amountOfComponents] = Data{};

	entityToIndex.erase( ent );
	entityToIndex[amountOfComponents] = index;

	indexToEntity[index] = indexToEntity[amountOfComponents];
	indexToEntity.erase( amountOfComponents );
}
