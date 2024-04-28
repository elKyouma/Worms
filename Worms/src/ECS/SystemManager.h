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
	void Render();

	template<typename Sys, typename... Args>
	void RegisterSystem( Args&&... params );

	void OnSignatureChange( const EntityId e, const Signature signature );
	void UnsubscribeEntity( const EntityId e );

	~SystemManager();

private:
	std::array<System*, MAX_SYSTEMS> systems{};
	size_t amountOfSystems{ 0 };
	ComponentManager& componentManager;
};

template<typename Sys, typename... Args>
inline void SystemManager::RegisterSystem( Args&&... params )
{
	systems[amountOfSystems++] = new Sys{ componentManager, std::forward<Args>( params )... };
}
