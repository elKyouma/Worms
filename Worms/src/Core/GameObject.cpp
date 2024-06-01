#include "Core/GameObject.h"
#include "Terminal/Terminal.h"

std::vector<std::unique_ptr<GameObject>>  GameObject::activeObjs;

void GameObject::Initialise( SDL_Renderer* newRenderer, World* newWorld )
{
	renderer = newRenderer;
	world = newWorld;
	objectId = world->CreateEntity();
	//Terminal::Get().Log(objectId + "", );
}
