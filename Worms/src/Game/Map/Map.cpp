#include "box2d/b2_chain_shape.h"
#include "box2d/b2_fixture.h"
#include "box2d/b2_polygon_shape.h"
#include "box2d/b2_world.h"
#include "Core/Physics/ColliderFactory.h"
#include "Core/Utils.h"
#include "ExceptionHandling/SDL_Exception.h"
#include "Game/Components.h"
#include "Game/Map/Map.h"

Map::Map( SDL_Renderer* renderer, World* world, b2World* physicsWorld ) : world( world )
{
	mapId = world->CreateEntity();
	pos = &world->AddComponent<Position>( mapId, { 1.5f, -1.f } );

	physTex = IMG_LoadPhysicTexture( renderer, "map.png" );
	if ( physTex.has_value() )
	{

		RigidBody& rb = world->AddComponent<RigidBody>( mapId );
		SDL_Point size;
		SDL_QueryTexture( physTex.value().texture, NULL, NULL, &size.x, &size.y );

		for ( auto& points : physTex.value().points )
		{
			points = DouglasPeucker( points, 0.02 );
			for ( auto& point : points ) {
				point.x -= size.x / 200.f;
				point.y += size.y / 200.f;
			}
		}

		bodyDef.position = { pos->x, pos->y };

		rb.body = physicsWorld->CreateBody( &bodyDef );
    
		b2ChainShape shape;
    
		shape.CreateLoop( &physTex.value().points[0][0], physTex.value().points[0].size() );
		rb.body = ColliderFactory::Get().CreateStaticBody( &shape, { pos->x - size.x / 200.f, pos->y + size.y / 200.f } ).GetBody();

		world->AddComponent<Sprite>( mapId, { physTex.value().texture } );
	}
	//else
		//TODO return error
}

Map::~Map()
{
	SDL_DestroyTexture( world->GetComponent<Sprite>( mapId ).texture );
}

void Map::Update( SDL_Renderer* renderer )
{
}
