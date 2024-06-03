#include "Game/Player/HealthBar.h"
#include <SDL2/SDL_image.h>
#include "ExceptionHandling/SDL_Exception.h"
#include "ECS/World.h"

HealthBar::HealthBar( SDL_Renderer* renderer, World* world, EntityId newParentId, int health)
{
	Initialise( renderer, world );

	position = &world->AddComponent<Position>( objectId, { 0, 0 } );
	hp = &world->AddComponent<Health>( objectId, { health } );
	target = &world->AddComponent<Follow>( objectId, { newParentId, 0.0, 0.3 } );

	Sprite& spriteComponent = world->AddComponent<Sprite>( objectId );
	spriteComponent.texture = IMG_LoadTexture( renderer, "heart.png" );
	SDL_CHECK( spriteComponent.texture );
}