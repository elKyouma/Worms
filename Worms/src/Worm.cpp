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
	wormId = world->CreateEntity();
	pos = &world->AddComponent<Position>( wormId );

	Sprite& spriteComponent = world->AddComponent<Sprite>( wormId );
	spriteComponent.texture = IMG_LoadTexture( renderer, "worms.png" );
	SDL_CHECK( spriteComponent.texture );

	rb = &world->AddComponent<RigidBody>( wormId );
	static b2BodyDef bodyDef;
	bodyDef.type = b2_kinematicBody;
	bodyDef.position = { pos->x, pos->y };
	bodyDef.fixedRotation = true;
	rb->body = physicsWorld->CreateBody( &bodyDef );

	static b2PolygonShape shape;
	shape.SetAsBox( 0.2, 0.4 );

	static b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.friction = 1;
	fixtureDef.density = 1;
	rb->body->CreateFixture( &fixtureDef );
}

Worm::~Worm()
{
	SDL_DestroyTexture( world->GetComponent<Sprite>( wormId ).texture );
}

void Worm::Update()
{
	//Add input and delta by using singletons
	rb->body->SetLinearVelocity( { Input::Get().Horizontal() * WORM_SPEED, Input::Get().Vertical() * WORM_SPEED } );
	pos->x = rb->body->GetPosition().x;
	pos->y = rb->body->GetPosition().y;
}
