#include "Worm.h"

#include <box2d/b2_contact.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_polygon_shape.h>
#include "ContactManager.h"
#include "ExceptionHandling/SDL_Exception.h"
#include "Input.h"
#include "Time.h"
#include "Utils.h"

Worm::Worm( SDL_Renderer* newRenderer, World* newWorld, b2World* physicsWorld )
{
	Initialise( newRenderer, newWorld );
	objectId = world->CreateEntity();
	pos = &world->AddComponent<Position>( objectId, { 2, 1 } );

	physicsInfo.tag = PhysicsTag::WORM;
	physicsInfo.id = objectId;

	Sprite& spriteComponent = world->AddComponent<Sprite>( objectId );
	spriteComponent.texture = IMG_LoadTexture( renderer, "worms.png" );
	SDL_CHECK( spriteComponent.texture );

	rb = &world->AddComponent<RigidBody>( objectId );
	static b2BodyDef bodyDef;
	//bodyDef.type = b2_kinematicBody;
	bodyDef.type = b2_dynamicBody;
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

	ContactManager::Get().AddEvent( objectId, CollisionType::BEGIN, [&] ( b2Contact* ) { grounded = true; } );
	ContactManager::Get().AddEvent( objectId, CollisionType::END, [&] ( b2Contact* ) { grounded = false; } );
}

Worm::~Worm()
{
	SDL_DestroyTexture( world->GetComponent<Sprite>( objectId ).texture );
}

void Worm::Update()
{
	pos->x = rb->body->GetPosition().x;
	pos->y = rb->body->GetPosition().y;

	if ( !active ) return;

	if ( abs( rb->body->GetLinearVelocity().x ) < 2 )
		rb->body->ApplyForce( { Input::Get().Horizontal() * WORM_SPEED * 10, 0.f }, { 0.f,0.f }, true );

	if ( IsGrounded() && Input::Get().Vertical() > 0.f && rb->body->GetLinearVelocity().y < 0.4 )
	{
		grounded = false;
		rb->body->ApplyLinearImpulse( { 0.f, JUMP_FORCE / 10.f }, { 0.f,0.f }, true );
	}
}

void Worm::Activate()
{
	active = true;
}

void Worm::Disactivate()
{
	active = false;
}

bool Worm::IsGrounded() const
{
	return grounded;
}
