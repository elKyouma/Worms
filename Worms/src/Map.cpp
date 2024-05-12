#include "box2d/b2_chain_shape.h"
#include "box2d/b2_fixture.h"
#include "box2d/b2_polygon_shape.h"
#include "box2d/b2_world.h"
#include "ECS/Components.h"
#include "ExceptionHandling/SDL_Exception.h"
#include "Map.h"
#include "Utils.h"

Map::Map( SDL_Renderer* renderer, World* world, b2World* physicsWorld ) : world( world )
{
	mapId = world->CreateEntity();
	pos = &world->AddComponent<Position>( mapId );
	pos->x = -1;
	pos->y = 2;
	Sprite& sprite = world->AddComponent<Sprite>( mapId );

	physTex = IMG_LoadPhysicTexture( renderer, "map.png" );
	if ( physTex.has_value() )
	{
		for ( int i = 0; i < physTex.value().points.size(); i++ )
			physTex.value().points[i] = DouglasPeucker( physTex.value().points[i], 0.02 );

		RigidBody& rb = world->AddComponent<RigidBody>( mapId );
		static b2BodyDef bodyDef;
		bodyDef.type = b2_staticBody;
		bodyDef.position = { pos->x, pos->y };
		rb.body = physicsWorld->CreateBody( &bodyDef );

		static b2ChainShape shape;
		shape.CreateLoop( &physTex.value().points[0][0], physTex.value().points[0].size() );

		static b2FixtureDef fixtureDef;
		fixtureDef.density = 1;
		fixtureDef.shape = &shape;
		rb.body->CreateFixture( &fixtureDef );

		sprite.texture = physTex.value().texture;
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
	DrawPolygon( renderer, physTex.value().points, { pos->x, pos->y } );
}
