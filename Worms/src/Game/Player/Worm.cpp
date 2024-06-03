#include <box2d/b2_contact.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_polygon_shape.h>
#include "Core/Input.h"
#include "Core/Physics/ContactManager.h"
#include "Core/Time.h"
#include "Core/Utils.h"
#include "ExceptionHandling/SDL_Exception.h"
#include "Game/Player/Worm.h"

Worm::Worm( SDL_Renderer* newRenderer, World* newWorld, b2World* physicsWorld, Camera camera )
{
	Initialise( newRenderer, newWorld );
	pos = &world->AddComponent<Position>( objectId, { 2, 1 } );

	physicsInfo.tag = PhysicsTag::WORM;
	physicsInfo.id = objectId;

	auto groundedId = world->CreateEntity();
	groundedPhysicsInfo.tag = PhysicsTag::GROUNDED;
	groundedPhysicsInfo.id = groundedId;

	Sprite& spriteComponent = world->AddComponent<Sprite>( objectId );
	spriteComponent.texture = IMG_LoadTexture( renderer, "worms.png" );
	SDL_CHECK( spriteComponent.texture );

	b2PolygonShape shape;

	shape.SetAsBox( 0.1, 0.2 );
	b2PolygonShape groundShape;
	groundShape.SetAsBox( 0.1, 0.05, { 0.f, -0.15f }, 0.f );

	collider = std::make_unique<Collider>( ColliderFactory::Get().CreateDynamicBody( &shape, { pos->x, pos->y }, physicsInfo ) );
	collider->FreezeRotation();
	ColliderFactory::Get().CreateTriggerFixture( collider->GetBody(), &groundShape, groundedPhysicsInfo );
	ContactManager::Get().AddEvent( groundedId, CollisionType::BEGIN,
									[&] ( b2Contact* ) {
										grounded = true;
									} );
	ContactManager::Get().AddEvent( groundedId, CollisionType::END,
									[&] ( b2Contact* ) {
										grounded = false;
									} );

	healthBar = std::make_unique<HealthBar>( newRenderer, newWorld, objectId, camera, 100 );
	rb = &world->AddComponent<RigidBody>( objectId );
	rb->body = collider->GetBody();
}

void Worm::Update()
{
	pos->x = rb->body->GetPosition().x;
	pos->y = rb->body->GetPosition().y;

	healthBar->Update();

	if ( !active ) return;

	if ( abs( rb->body->GetLinearVelocity().x ) < 2 )
		rb->body->SetLinearVelocity( { Input::Get().Horizontal() * WORM_SPEED, rb->body->GetLinearVelocity().y });

	if ( IsGrounded() && Input::Get().Jump() && rb->body->GetLinearVelocity().y < 0.4 )
	{
		grounded = false;
		rb->body->SetLinearVelocity( { rb->body->GetLinearVelocity().x * sqrtf(2.0), JUMP_FORCE * sqrtf( 2.0 ) });
	}
}

void Worm::CleanUp()
{
	SDL_DestroyTexture( world->GetComponent<Sprite>( objectId ).texture );
}

void Worm::Render() {
	healthBar->Render();
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
