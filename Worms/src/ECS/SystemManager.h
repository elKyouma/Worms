#pragma once
#include <array>
#include <set>
#include "ECS_Types.h"

class System
{
public:
	virtual void Update() {};
	inline Signature GetSystemSignature() const { return systemSignature; }
	bool CheckIfSubscribed( EntityId ent ) const { return subscribed.find( ent ) != subscribed.end(); }
	void Subscribe( EntityId ent ) { subscribed.insert( ent ); }
	void Unsubscribe( EntityId ent ) { subscribed.erase( ent ); }
private:
	Signature systemSignature;
	std::set<EntityId> subscribed;
};

class SystemManager
{
public:
	void Update();

	template<typename Sys>
	void RegisterSystem();

	void OnSignatureChange( EntityId e, Signature signature );

	~SystemManager();

private:
	std::array<System*, MAX_SYSTEMS> systems;

	size_t amountOfSystems{ 0 };
};

template<typename Sys>
inline void SystemManager::RegisterSystem()
{
	systems[amountOfSystems++] = new Sys{};
}
