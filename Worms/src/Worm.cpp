#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "ExceptionHandling/SDL_Exception.h"
#include "Worm.h"

Worm::Worm( SDL_Renderer* renderer, World* world ) : world( world )
{
	wormId = world->CreateEntity();
	world->AddComponent<Position>( wormId );
	Sprite& spriteComponent = world->AddComponent<Sprite>( wormId );
	motion = &world->AddComponent<Motion>( wormId );
	motion->v_y = 0.05;

	SDL_Surface* temp = IMG_Load( "worms.png" );
	if ( temp == NULL )
		printf( "IMG_Load: %s\n", IMG_GetError() );
	spriteComponent.texture = SDL_CreateTextureFromSurface( renderer, temp );
	SDL_CHECK( spriteComponent.texture );
	SDL_FreeSurface( temp );
}

Worm::~Worm()
{
	SDL_DestroyTexture( world->GetComponent<Sprite>( wormId ).texture );
}

void Worm::Update()
{
	//Add input and delta by using singletons
}