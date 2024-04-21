#pragma once
#include <array>
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

private:
	std::array<IComponentArray, MAX_COMPONENTS* MAX_ENTITIES> components;
	std::unordered_map<const char*, uint16_t> typeToComponentId;
	uint8_t registeredComponents = 0u;

};

template<typename T>
inline void ComponentManager::RegisterComponent()
{
	typeToComponentId = registeredComponents;
	registeredComponents++;
}

template<typename T>
inline ComponentArray<T>& ComponentManager::GetComponentArray()
{

}

template<typename T>
inline T& ComponentManager::GetComponent( EntityId ent )
{

}

template<typename T>
inline T& ComponentManager::AddComponent( EntityId ent )
{

}
