#include "Game/Player/HealthBar.h"
#include <SDL2/SDL_image.h>
#include "ExceptionHandling/SDL_Exception.h"
#include "ECS/World.h"

HealthBar::HealthBar( SDL_Renderer* renderer, World* world, EntityId newParentId, int health)
{
	Initialise( renderer, world );

	parentId = newParentId;

	position = &world->AddComponent<Position>( objectId, { 0, 0 } );
	hp = &world->AddComponent<Health>( objectId, { health } );

	Sprite& spriteComponent = world->AddComponent<Sprite>( objectId );
	spriteComponent.texture = IMG_LoadTexture( renderer, "heart.png" );
	SDL_CHECK( spriteComponent.texture );
}

void HealthBar::Update()
{
	Position parentPosition = world->GetComponent<Position>( parentId );
	position->x = parentPosition.x;
	position->y = parentPosition.y + 0.3;
}
