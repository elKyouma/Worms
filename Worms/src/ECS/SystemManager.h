#pragma once
#include <array>
#include "ComponentManager.h"
#include "ECS_Types.h"
#include "System.h"

class SystemManager
{
public:
	SystemManager( ComponentManager& componentManager ) : componentManager( componentManager ) {}
	void Update();

	template<typename Sys>
	void RegisterSystem();

	void OnSignatureChange( EntityId e, Signature signature );

	~SystemManager();

private:
	std::array<System*, MAX_SYSTEMS> systems;
	size_t amountOfSystems{ 0 };
	ComponentManager& componentManager;
};

template<typename Sys>
inline void SystemManager::RegisterSystem()
{
	systems[amountOfSystems++] = new Sys{ componentManager };
}
