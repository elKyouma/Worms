#include "Game/Weapon/Weapon.h"
#include "SDL2/SDL_image.h"
#include "ExceptionHandling/SDL_Exception.h"
#include "Core/Time.h"
#include "Core/Input.h"

Weapon::Weapon( SDL_Renderer* newRenderer, World* newWorld )
{
	Initialise( newRenderer, newWorld );
	pos = &world->AddComponent<Position>( objectId, { 0, 0 } );

	rot = &world->AddComponent<Rotation>( objectId, { 0 });

	Sprite& spriteComponent = world->AddComponent<Sprite>( objectId );
	spriteComponent.texture = IMG_LoadTexture( renderer, "placeHolderWeapon.png" );
	SDL_CHECK( spriteComponent.texture );

}
void Weapon::Update()
{
	SDL_Point size;
	SDL_QueryTexture( world->GetComponent<Sprite>( objectId ).texture, NULL, NULL, &size.x, &size.y );
	pos->x = world->GetComponent<Position>( parentId ).x;
	pos->y = world->GetComponent<Position>( parentId ).y;

	rot->degree -= Input::Get().Vertical() * Time::deltaTime * 100.0;

	pos->x -=  0.1 * cos(rot->degree * M_PI / 180);
	pos->y -=  0.1 * sin( rot->degree * M_PI / 180 );
	

}

void Weapon::Use( )
{
	
}


Weapon::~Weapon()
{
	SDL_DestroyTexture( world->GetComponent<Sprite>( objectId ).texture );
}