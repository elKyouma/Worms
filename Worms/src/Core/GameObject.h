#pragma once
#include <vector>
#include "ECS/ECS_Types.h"
#include "ECS/World.h"
#include "SDL2/SDL.h"

class GameObject
{
public:
	virtual void Initialise( SDL_Renderer* newRenderer, World* newWorld );
	virtual void Update() {};
	virtual void Render() {};
	EntityId GetId() { return objectId; }

	static std::vector<std::unique_ptr<GameObject>>  activeObjs;

protected:
	EntityId objectId;
	World* world = nullptr;
	SDL_Renderer* renderer = nullptr;
};

