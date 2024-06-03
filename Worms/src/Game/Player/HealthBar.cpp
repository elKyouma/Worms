#include "Game/Player/HealthBar.h"
#include <SDL2/SDL_image.h>
#include "ExceptionHandling/SDL_Exception.h"
#include "ECS/World.h"

HealthBar::HealthBar( SDL_Renderer* renderer, World* world, EntityId newParentId, const Camera& camera, int health, SDL_Texture* texture): camera(camera)
{
	Initialise( renderer, world );

	position = &world->AddComponent<Position>( objectId, { 0, 0 } );
	hp = &world->AddComponent<Health>( objectId, { 100, 100 } );
	target = &world->AddComponent<Follow>( objectId, { newParentId, 0.0, 0.3 } );
	healthBar = texture;
	SDL_CHECK( healthBar );
}

void HealthBar::Render()
{
	SDL_Point size;
	SDL_QueryTexture( healthBar, NULL, NULL, &size.x, &size.y );

	double hpPrc = static_cast<float>(hp->current) / static_cast<float>(hp->max);
	SDL_Rect slice(0, 0, static_cast<int>(size.x) * hpPrc, size.y );

	SDL_Rect renderQuad(
		400 + static_cast<int>((position->x - camera.X()) * 100.0) - size.x / 2,
		300 - static_cast<int>((position->y - camera.Y()) * 100.0) - size.y / 2,
		slice.w,
		slice.h );

	SDL_RenderCopy( renderer, healthBar, &slice, &renderQuad );
}