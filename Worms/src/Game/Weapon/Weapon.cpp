#include <algorithm>
#include "Core/Input.h"
#include "Core/Time.h"
#include "ExceptionHandling/SDL_Exception.h"
#include "Game/Tags.h"
#include "Game/Weapon/Weapon.h"
#include "SDL2/SDL_image.h"

Weapon::Weapon( SDL_Renderer* newRenderer, World* newWorld, Camera* camera ) : camera( camera )
{
	Initialise( newRenderer, newWorld );
	pos = &world->AddComponent<Position>( objectId, { 0, 0 } );

	rot = &world->AddComponent<Rotation>( objectId, { 0 } );

	Sprite& spriteComponent = world->AddComponent<Sprite>( objectId );
	spriteComponent.texture = IMG_LoadTexture( renderer, "placeHolderWeapon.png" );
	SDL_CHECK( spriteComponent.texture );

	powerBar = IMG_LoadTexture( renderer, "powerBar.png" );
}
void Weapon::Update()
{
	pos->x = world->GetComponent<Position>( parentId ).x;
	pos->y = world->GetComponent<Position>( parentId ).y;

	rot->degree += Input::Get().Vertical() * static_cast<float>(Time::deltaTime) * 100.f;

	pos->x += 0.1f * cosf( rot->degree * static_cast<float>(M_PI) / 180 );
	pos->y += 0.1f * sinf( rot->degree * static_cast<float>(M_PI) / 180 );

	for ( auto& projectille : projectilles )
		projectille->Update();

	if ( Input::Get().UseAction() )
	{
		if ( force < 0.25 )
			force += 0.25f * static_cast<float>(Time::deltaTime);
	}
	else
	{
		if ( force )
		{
			projectilles.emplace_back();
			projectilles.back() = std::make_unique<Projectille>( renderer, world );
			projectilles.back()->Initialise( pos->x + 0.5f * cosf( rot->degree * static_cast<float>(M_PI) / 180 ),
											 pos->y + 0.5f * sinf( rot->degree * static_cast<float>(M_PI) / 180 ),
											 force * cosf( rot->degree * static_cast<float>(M_PI) / 180 ),
											 force * sinf( rot->degree * static_cast<float>(M_PI) / 180 ) );
		}
		force = 0;
	}
}

void Weapon::Render()
{
	SDL_Point size;
	SDL_QueryTexture( powerBar, NULL, NULL, &size.x, &size.y );

	SDL_Rect slice(
		0,
		0,
		static_cast<int>(size.x * force / 0.25),
		size.y );

	SDL_Rect renderQuad(
		400 + static_cast<int>((pos->x - camera->X()) * 100.0),
		300 - static_cast<int>((pos->y - camera->Y()) * 100.0) - size.y / 2,
		slice.w,
		slice.h );

	SDL_Point centre( 0, size.y / 2 );


	SDL_RenderCopyEx( renderer, powerBar, &slice, &renderQuad, -rot->degree, &centre, SDL_FLIP_NONE );
}

void Weapon::DestroyProjectille( EntityId ID )
{
	projectilles.erase( std::remove_if( projectilles.begin(), projectilles.end(),
						[ID] ( std::unique_ptr<Projectille>& proc ) { return proc->GetId() == ID; } ), projectilles.end() );
}


Weapon::~Weapon()
{
	SDL_DestroyTexture( world->GetComponent<Sprite>( objectId ).texture );
}