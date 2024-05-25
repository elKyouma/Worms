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
	pos->x = world->GetComponent<Position>( parentId ).x;
	pos->y = world->GetComponent<Position>( parentId ).y;

	rot->degree -= Input::Get().Vertical() * Time::deltaTime * 100.0;

	pos->x -=  0.1 * cos(rot->degree * M_PI / 180);
	pos->y -=  0.1 * sin( rot->degree * M_PI / 180 );

	if ( Input::Get().UseAction() )
	{
		if( force < 10.0 )
			force += 1 * Time::deltaTime;
	}
	else
	{
		ImGui::End();
		if ( force )
		{
			//new projectille
		}
		force = 0;
	}

}


Weapon::~Weapon()
{
	SDL_DestroyTexture( world->GetComponent<Sprite>( objectId ).texture );
}