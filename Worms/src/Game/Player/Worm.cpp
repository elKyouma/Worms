#include <box2d/b2_contact.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_polygon_shape.h>
#include "Core/Input.h"
#include "Core/Physics/ContactManager.h"
#include "Core/Time.h"
#include "Core/Utils.h"
#include "ExceptionHandling/SDL_Exception.h"
#include "Game/Player/Worm.h"

Worm::Worm( SDL_Renderer* newRenderer, World* newWorld, b2World* physicsWorld, const Camera& camera, SDL_Texture* texture )
{
	Initialise( newRenderer, newWorld );
	static float posX = -2.f;
	posX += 1.f;
	auto& pos = world->AddComponent<Position>( objectId, { posX, 2 } );

	physicsInfo.tag = PhysicsTag::WORM;
	physicsInfo.id = objectId;


	ContactManager::Get().AddEvent( objectId, CollisionType::BEGIN,
									[&] ( b2Contact* contact )
									{
										auto entId = GetEntityWithTag( contact, PhysicsTag::DESTRUCTION_FIELD );
										if ( entId.has_value() )
											healthBar->TakeDamage( 40 );
									} );

	groundedId = world->CreateEntity();
	groundedPhysicsInfo.tag = PhysicsTag::GROUNDED;
	groundedPhysicsInfo.id = groundedId;

	Sprite& spriteComponent = world->AddComponent<Sprite>( objectId );
	spriteComponent.texture = IMG_LoadTexture( renderer, "worms.png" );
	SDL_CHECK( spriteComponent.texture );

	b2PolygonShape shape;

	shape.SetAsBox( 0.08, 0.1 );
	b2PolygonShape groundShape;
	groundShape.SetAsBox( 0.05, 0.05, { 0.f, -0.08f }, 0.f );

	collider = std::make_unique<Collider>( ColliderFactory::Get().CreateDynamicBody( &shape, { pos.x, pos.y }, physicsInfo ) );
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

	healthBar = std::make_unique<HealthBar>( newRenderer, newWorld, objectId, camera, 100, texture );
	world->AddComponent<RigidBody>( objectId, { collider->GetBody() } );
}

void Worm::Update( std::vector<Worm*>& wormsToDelete )
{
	if ( world->GetComponent<Position>( objectId ).y < -15.f ) healthBar->TakeDamage( 100 );
	auto& rb = world->GetComponent<RigidBody>( objectId );
	healthBar->Update();

	if ( healthBar->getCurrentHp() <= 0 )
		wormsToDelete.emplace_back( this );

	if ( !active ) return;

	if ( abs( rb.body->GetLinearVelocity().x ) < 2 )
		rb.body->SetLinearVelocity( { Input::Get().Horizontal() * WORM_SPEED, rb.body->GetLinearVelocity().y } );

	Jump();
}

void Worm::Jump()
{
	auto& rb = world->GetComponent<RigidBody>( objectId );
	if ( !IsGrounded() || !Input::Get().Jump() || rb.body->GetLinearVelocity().y > 0.4 ) return;

	grounded = false;
	rb.body->SetLinearVelocity( { rb.body->GetLinearVelocity().x * sqrtf( 2.0 ), JUMP_FORCE * sqrtf( 2.0 ) } );
	jumpSound.Play();
}

void Worm::CleanUp()
{
	ColliderFactory::Get().GetPhysicsWorld()->DestroyBody( collider->GetBody() );
	world->DestroyEntity( groundedId );
	ContactManager::Get().ClearEvent( groundedId, CollisionType::BEGIN );
	ContactManager::Get().ClearEvent( groundedId, CollisionType::END );
	healthBar->CleanUp();
	GameObject::CleanUp();
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
