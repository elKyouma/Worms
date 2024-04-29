#include "ECS/Components.h"
#include "ExceptionHandling/SDL_Exception.h"
#include "Map.h"
#include "Utils.h"

Map::Map( SDL_Renderer* renderer, World* world ) : world( world )
{
	mapId = world->CreateEntity();
	world->AddComponent<Position>( mapId );
	Sprite& sprite = world->AddComponent<Sprite>( mapId );

	sprite.texture = IMG_LoadTexture( renderer, "map.png" );
	SDL_CHECK( sprite.texture );
}

Map::~Map()
{
	SDL_DestroyTexture( world->GetComponent<Sprite>( mapId ).texture );
}
