#pragma once

#include <array>
#include <sstream>
#include "ComponentArray.h"
#include "ECS_Types.h"

class ComponentManager
{
public:
	template<typename T>
	void RegisterComponent();;

	template<typename T>
	ComponentArray<T>& GetComponentArray();

	template<typename T>
	T& GetComponent( EntityId ent );

	template<typename T>
	T& AddComponent( EntityId ent );

	std::vector<std::string> GetRegisteredComponents();

	~ComponentManager();
private:
	std::array<IComponentArray*, MAX_COMPONENTS> components;
	std::unordered_map<const char*, uint8_t> typeToComponentId;
	uint8_t registeredComponents = 0u;

};

template<typename T>
void ComponentManager::RegisterComponent()
{
	if ( registeredComponents == MAX_COMPONENTS )
		ECS_THROW( "ComponentArray overflow" );

	components[registeredComponents] = new ComponentArray<T>();
	typeToComponentId.insert( { typeid(T).name(), registeredComponents++ } );
}

template<typename T>
ComponentArray<T>& ComponentManager::GetComponentArray()
{
	auto it = typeToComponentId.find( typeid(T).name() );
	if ( it == typeToComponentId.end() )
		ECS_THROW( "You are trying to access unregistered component array" );
	EntityId index = it->second;
	return *static_cast<ComponentArray<T>*> (components[index]);
}

template<typename T>
T& ComponentManager::GetComponent( EntityId ent )
{
	return GetComponentArray<T>().GetData( ent );
}

template<typename T>
T& ComponentManager::AddComponent( EntityId ent )
{
	return GetComponentArray<T>().AddData( ent );
}

std::vector<std::string> ComponentManager::GetRegisteredComponents()
{
	std::vector<std::string> result{};
	for ( auto it = typeToComponentId.begin(); it != typeToComponentId.end(); it++ )
		result.push_back( it->first );

	return result;
}

ComponentManager::~ComponentManager()
{
	for ( int i = 0; i < registeredComponents; i++ )
		delete components[i];
}
