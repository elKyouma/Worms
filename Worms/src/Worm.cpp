#include "Worm.h"

#include <box2d/b2_fixture.h>
#include <box2d/b2_polygon_shape.h>
#include <SDL2/SDL.h>
#include "ExceptionHandling/SDL_Exception.h"
#include "Input.h"
#include "Time.h"
#include "Utils.h"

Worm::Worm( SDL_Renderer* renderer, World* world, b2World* physicsWorld ) : world( world )
{
	physicsInfo.tag = PhysicsTag::WORM;

	wormId = world->CreateEntity();
	pos = &world->AddComponent<Position>( wormId, { 2, 1 } );

	Sprite& spriteComponent = world->AddComponent<Sprite>( wormId );
	spriteComponent.texture = IMG_LoadTexture( renderer, "worms.png" );
	SDL_CHECK( spriteComponent.texture );

	rb = &world->AddComponent<RigidBody>( wormId );
	static b2BodyDef bodyDef;
	bodyDef.type = b2_kinematicBody;
	//bodyDef.type = b2_dynamicBody;
	bodyDef.position = { pos->x, pos->y };
	bodyDef.fixedRotation = true;
	bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(this);
	rb->body = physicsWorld->CreateBody( &bodyDef );

	static b2PolygonShape shape;
	shape.SetAsBox( 0.1, 0.2 );

	static b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.friction = 1;
	fixtureDef.density = 1;
	fixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(&physicsInfo);
	rb->body->CreateFixture( &fixtureDef );
}

Worm::~Worm()
{
	SDL_DestroyTexture( world->GetComponent<Sprite>( wormId ).texture );
}

void Worm::Update()
{
	rb->body->SetLinearVelocity( { Input::Get().Horizontal() * WORM_SPEED, -2.f } );

	//rb->body->ApplyForceToCenter( { Input::Get().Horizontal() * WORM_SPEED, Input::Get().Vertical() * WORM_SPEED }, true );
	pos->x = rb->body->GetPosition().x;
	pos->y = rb->body->GetPosition().y;
}

void Worm::Activate()
{
}

void Worm::Disactivate()
{
}
