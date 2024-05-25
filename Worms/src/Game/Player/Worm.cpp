#include <box2d/b2_contact.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_polygon_shape.h>
#include "Core/Input.h"
#include "Core/Physics/ContactManager.h"
#include "Core/Time.h"
#include "Core/Utils.h"
#include "ExceptionHandling/SDL_Exception.h"
#include "Game/Player/Worm.h"

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

	b2PolygonShape shape;
  
	shape.SetAsBox( 0.1, 0.2 );
	b2PolygonShape groundShape;
	groundShape.SetAsBox( 0.1, 0.05, { 0.f, -0.25f }, 0.f );

	collider = std::make_unique<Collider>( ColliderFactory::Get().CreateDynamicBody( &shape, { pos->x, pos->y } ) );
	collider->FreezeRotation();
	ColliderFactory::Get().CreateTriggerFixture( collider->GetBody(), &groundShape, physicsInfo );
	ContactManager::Get().AddEvent( objectId, CollisionType::BEGIN,
									[&] ( b2Contact* ) {
										grounded = true;
									} );
	ContactManager::Get().AddEvent( objectId, CollisionType::END,
									[&] ( b2Contact* ) {
										grounded = false;
									} );

	healthBar = std::make_unique<HealthBar>( newRenderer, newWorld, objectId, 100 );
	rb = &world->AddComponent<RigidBody>( objectId );
	rb->body = collider->GetBody();
}

Worm::~Worm()
{
	SDL_DestroyTexture( world->GetComponent<Sprite>( objectId ).texture );
}

void Worm::Update()
{
	pos->x = rb->body->GetPosition().x;
	pos->y = rb->body->GetPosition().y;

	healthBar->Update();

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
