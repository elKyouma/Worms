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

	physTex = IMG_LoadPhysicTexture( renderer, "map.png" );
	if ( physTex.has_value() )
	{

		RigidBody& rb = world->AddComponent<RigidBody>( mapId );
		auto texture = SDL_CreateTextureFromSurface( renderer, physTex.value().surface );
		SDL_Point size;
		SDL_QueryTexture( texture, NULL, NULL, &size.x, &size.y );

		for ( auto& points : physTex.value().points )
		{
			points = DouglasPeucker( points, 0.02 );
			for ( auto& point : points ) {
				point.x -= size.x / 200.f;
				point.y += size.y / 200.f;
			}
		}

		b2ChainShape shape;
		shape.CreateLoop( &physTex.value().points[0][0], physTex.value().points[0].size() );
		auto collider = ColliderFactory::Get().CreateStaticBody( &shape, { pos->x, pos->y }, physicsInfo );
		collider.AddOnColliderEnter( std::bind( &Map::DestroyMap, this, std::placeholders::_1 ) );
		collider.AddOnColliderExit( std::bind( &Map::DestroyMap, this, std::placeholders::_1 ) );
		rb.body = collider.GetBody();

		world->AddComponent<Sprite>( mapId, { texture } );
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

	SDL_Point size{};
	SDL_QueryTexture( world->GetComponent<Sprite>( mapId ).texture, NULL, NULL, &size.x, &size.y );
	Position mapPos = world->GetComponent<Position>( mapId );
	b2Vec2 localSpace = { bulltetPos.x - mapPos.x, -bulltetPos.y + mapPos.y };
	SDL_Point point = { localSpace.x * 100, localSpace.y * 100 };
	point.x += size.x / 2;
	point.y += size.y / 2;
	auto surf = physTex.value().surface;
	SDL_LockSurface( surf );
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

	auto points = MarchingSquares( (Uint32*)surf->pixels, surf->w, surf->h, 64 );
	std::vector<std::vector<b2Vec2>> physPoints;
	for ( int i = 0; i < points.size(); i++ )
	{
		physPoints.push_back( {} );
		for ( int j = points[i].size() - 1; j >= 0; j-- )
			physPoints[i].emplace_back( float( points[i][j].x / 100.f ), float( -points[i][j].y / 100.f ) );
	}
	physTex->points.clear();
	physTex->points = physPoints;
	SDL_UnlockSurface( surf );

	for ( auto& points : physTex.value().points )
	{
		points = DouglasPeucker( points, 0.02 );
		for ( auto& point : points ) {
			point.x -= size.x / 200.f;
			point.y += size.y / 200.f;
		}
	}

	physicsWorld->DestroyBody( world->GetComponent<RigidBody>( mapId ).body );
	b2ChainShape shape;
	shape.CreateLoop( &physTex.value().points[0][0], physTex.value().points[0].size() );
	auto collider = ColliderFactory::Get().CreateStaticBody( &shape, { pos->x, pos->y }, physicsInfo );
	collider.AddOnColliderEnter( std::bind( &Map::DestroyMap, this, std::placeholders::_1 ) );
	collider.AddOnColliderExit( std::bind( &Map::DestroyMap, this, std::placeholders::_1 ) );
	world->GetComponent<RigidBody>( mapId ).body = collider.GetBody();

	auto texture = SDL_CreateTextureFromSurface( renderer, physTex.value().surface );
	SDL_QueryTexture( texture, NULL, NULL, &size.x, &size.y );
	SDL_DestroyTexture( world->GetComponent<Sprite>( mapId ).texture );
	world->GetComponent<Sprite>( mapId ).texture = texture;

}

void Map::DestroyMap( b2Contact* contact )
{
	if ( reinterpret_cast<PhysicsInfo*>(contact->GetFixtureA()->GetUserData().pointer)->tag == PhysicsTag::BULLET )
		bulltetPos = world->GetComponent<Position>( reinterpret_cast<PhysicsInfo*>(contact->GetFixtureA()->GetUserData().pointer)->id );
	else if ( reinterpret_cast<PhysicsInfo*>(contact->GetFixtureB()->GetUserData().pointer)->tag == PhysicsTag::BULLET )
		bulltetPos = world->GetComponent<Position>( reinterpret_cast<PhysicsInfo*>(contact->GetFixtureB()->GetUserData().pointer)->id );
	else
		return;

	if ( destroyed ) return;

	destroyed = true;
}

float Map::Distance( const float x1, const float y1, const float x2, const float y2 )
{
	return std::sqrt( std::pow( x2 - x1, 2 ) + std::pow( y2 - y1, 2 ) );
}
