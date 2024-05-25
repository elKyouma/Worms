#include "Core/GameObject.h"

void GameObject::Initialise( SDL_Renderer* newRenderer, World* newWorld )
{
	renderer = newRenderer;
	world = newWorld;
	objectId = world->CreateEntity();
}
