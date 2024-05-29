#include <memory>
#include "box2d/b2_chain_shape.h"
#include "box2d/b2_fixture.h"
#include "box2d/b2_polygon_shape.h"
#include "box2d/b2_world.h"
#include "Core/Physics/ColliderFactory.h"
#include "Core/Physics/ContactManager.h"
#include "Core/Utils.h"
#include "ExceptionHandling/SDL_Exception.h"
#include "Game/Components.h"
#include "Game/Map/Map.h"
#include "SDL2/SDL_surface.h"

Map::Map( SDL_Renderer* renderer, World* world, b2World* physicsWorld ) : world( world ), renderer( renderer ), physicsWorld( physicsWorld )
{
	mapId = world->CreateEntity();
	physicsInfo.id = mapId;
	physicsInfo.tag = PhysicsTag::MAP;
	pos = &world->AddComponent<Position>( mapId, { 1.5f, -1.f } );
	sprite = &world->AddComponent<Sprite>( mapId );

	physTex = IMG_LoadPhysicTexture( renderer, "map.png" );
	if ( physTex.has_value() )
	{
		auto& rb = world->AddComponent<RigidBody>( mapId );
		auto texture = SDL_CreateTextureFromSurface( renderer, physTex.value().surface );
		SDL_QueryTexture( texture, NULL, NULL, &mapSize.x, &mapSize.y );
		CreateNewColliders();

		sprite->texture = texture;
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
	if ( !destroyed || physicsWorld->IsLocked() ) return;
	destroyed = false;

	Position mapPos = world->GetComponent<Position>( mapId );
	SDL_Surface( GlobalToLocalPos( mapPos ) );
	CreateNewColliders();

	auto texture = SDL_CreateTextureFromSurface( renderer, physTex.value().surface );
	SDL_DestroyTexture( world->GetComponent<Sprite>( mapId ).texture );
	sprite->texture = texture;
}

SDL_Point Map::GlobalToLocalPos( const Position& mapPos )
{
	b2Vec2 localSpace = { bulltetPos.x - mapPos.x, -bulltetPos.y + mapPos.y };
	SDL_Point point = { localSpace.x * 100, localSpace.y * 100 };
	point.x += mapSize.x / 2;
	point.y += mapSize.y / 2;
	return point;
}

void Map::SDL_Surface( SDL_Point point )
{
	auto surf = physTex.value().surface;
	for ( int y = 0; y < surf->h; y++ )
	{
		for ( int x = 0; x < surf->w; x++ )
		{
			float dist = Distance( x, y, point.x, point.y );
			Uint8* pixel = (Uint8*)surf->pixels;
			pixel += (y * surf->pitch) + (x * sizeof( Uint32 ));

			if ( dist < 100 )
				*((Uint32*)pixel) &= 0x00FFFFFF;
		}

	}
}

void Map::DestroyMap( b2Contact* contact )
{
	auto entId = GetEntityWithTag( contact, PhysicsTag::BULLET );
	if ( !entId.has_value() ) return;

	bulltetPos = world->GetComponent<Position>( entId.value() );

	if ( destroyed ) return;

	destroyed = true;
}

float Map::Distance( const float x1, const float y1, const float x2, const float y2 )
{
	return std::sqrt( std::pow( x2 - x1, 2 ) + std::pow( y2 - y1, 2 ) );
}

void Map::CreateNewColliders()
{
	auto surf = physTex->surface;
	SDL_LockSurface( surf );

	auto shapes = MarchingSquares( (Uint32*)surf->pixels, surf->w, surf->h, 64 );
	std::vector<std::vector<b2Vec2>> physPoints;
	for ( int i = 0; i < shapes.size(); i++ )
	{
		physPoints.push_back( {} );
		for ( int j = shapes[i].size() - 1; j >= 0; j-- )
			physPoints[i].emplace_back( float( shapes[i][j].x / 100.f ), float( -shapes[i][j].y / 100.f ) );
	}
	for ( auto& points : physPoints )
	{
		points = DouglasPeucker( points, 0.02 );
		for ( auto& point : points ) {
			point.x -= mapSize.x / 200.f;
			point.y += mapSize.y / 200.f;
		}
	}

	physTex->points.clear();
	physTex->points = physPoints;

	SDL_UnlockSurface( surf );

	if ( world->GetComponent<RigidBody>( mapId ).body != NULL )
		physicsWorld->DestroyBody( world->GetComponent<RigidBody>( mapId ).body );

	b2ChainShape shape;
	shape.CreateLoop( &physTex->points[0][0], physTex->points[0].size() );
	auto collider = ColliderFactory::Get().CreateStaticBody( &shape, { pos->x, pos->y }, physicsInfo );
	for ( int i = 1; i < physTex->points.size(); i++ )
	{
		shape.Clear();
		shape.CreateLoop( &physTex.value().points[i][0], physTex.value().points[i].size() );
		ColliderFactory::Get().CreateStaticFixture( collider.GetBody(), &shape, physicsInfo );
	}
	collider.AddOnColliderEnter( std::bind( &Map::DestroyMap, this, std::placeholders::_1 ) );
	collider.AddOnColliderExit( std::bind( &Map::DestroyMap, this, std::placeholders::_1 ) );
	world->GetComponent<RigidBody>( mapId ).body = collider.GetBody();

}
