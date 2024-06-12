#include "Core/Camera/FocusPoint.h"

FocusPoint::FocusPoint( SDL_Renderer* newRenderer, World* newWorld )
{
	GameObject::Initialise( newRenderer, newWorld );
	pos = &world->AddComponent<Position>( objectId, { 2, -1 } );
	target = &world->AddComponent<Follow>( objectId, { 3 } );
}