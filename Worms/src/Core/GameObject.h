#pragma once
#include "ECS/ECS_Types.h"
#include "ECS/World.h"
#include "SDL2/SDL.h"

class GameObject
{
public:
	GameObject() : renderer(nullptr), world(nullptr) {};
	void Initialise( SDL_Renderer* newRenderer, World* newWorld );
	virtual void Update() {};
	virtual void Render() {};
	EntityId getId() { return objectId; }

protected:
	EntityId objectId;
	World* world;
	SDL_Renderer* renderer;
};

