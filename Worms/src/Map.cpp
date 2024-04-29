#include <SDL2/SDL_image.h>
#include "ECS/Components.h"
#include "ExceptionHandling/SDL_Exception.h"
#include "Map.h"

Map::Map( SDL_Renderer* renderer, World* world ) : world( world )
{
	mapId = world->CreateEntity();
	world->AddComponent<Position>( mapId );
	Sprite& sprite = world->AddComponent<Sprite>( mapId );

	SDL_Surface* temp = IMG_Load( "map.png" );
	if ( temp == NULL )
		printf( "IMG_Load: %s\n", IMG_GetError() );
	sprite.texture = SDL_CreateTextureFromSurface( renderer, temp );
	SDL_CHECK( sprite.texture );
	SDL_FreeSurface( temp );
}

Map::~Map()
{
	SDL_DestroyTexture( world->GetComponent<Sprite>( mapId ).texture );
}
