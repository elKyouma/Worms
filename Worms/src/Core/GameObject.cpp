#include "Core/GameObject.h"
#include "Terminal/Terminal.h"

void GameObject::Initialise( SDL_Renderer* newRenderer, World* newWorld )
{
	renderer = newRenderer;
	world = newWorld;
	objectId = world->CreateEntity();
	//Terminal::Get().Log(objectId + "", );
}
