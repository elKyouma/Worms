#pragma once
#include <array>
#include <set>
#include "ECS_Types.h"

class System
{
public:
	virtual void Update() = 0;
private:
	std::set<Entity> subscribed;
};

class SystemManager
{
public:
	void Update();
	void RegisterSystem( System& sys );

	void OnSignatureChange( Entity e );

private:
	std::array<System, MAX_SYSTEMS> systems;

	size_t amountOfSystems{ 0 };
};

