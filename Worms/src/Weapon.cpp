#include "Weapon.h"
#include "SDL2/SDL_image.h"
#include "ExceptionHandling/SDL_Exception.h"

Weapon::Weapon( SDL_Renderer* renderer, World* world, EntityId parentId ) : world(world), parentId(parentId)
{
	weaponId = world->CreateEntity();
	pos = &world->AddComponent<Position>( weaponId, { 
		world->GetComponent<Position>(parentId).x, 
		world->GetComponent<Position>( parentId ).y });

	rot = &world->AddComponent<Rotation>( weaponId, { 0 });

	Sprite& spriteComponent = world->AddComponent<Sprite>( weaponId );
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
	SDL_DestroyTexture( world->GetComponent<Sprite>( weaponId ).texture );
}