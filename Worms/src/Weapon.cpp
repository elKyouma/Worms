#include "Weapon.h"
#include "SDL2/SDL_image.h"
#include "ExceptionHandling/SDL_Exception.h"

Weapon::Weapon( SDL_Renderer* newRenderer, World* newWorld, EntityId parentId ) : parentId(parentId)
{
	Initialise( newRenderer, newWorld );
	pos = &world->AddComponent<Position>( objectId, { 
		world->GetComponent<Position>(parentId).x, 
		world->GetComponent<Position>( parentId ).y });

	rot = &world->AddComponent<Rotation>( objectId, { 0 });

	Sprite& spriteComponent = world->AddComponent<Sprite>( objectId );
	spriteComponent.texture = IMG_LoadTexture( renderer, "placeHolderWeapon.png" );
	SDL_CHECK( spriteComponent.texture );

}
void Weapon::Update()
{
	pos->x = world->GetComponent<Position>( parentId ).x;
	pos->y = world->GetComponent<Position>( parentId ).y;
}

void Weapon::Use( )
{
	
}


Weapon::~Weapon()
{
	SDL_DestroyTexture( world->GetComponent<Sprite>( objectId ).texture );
}