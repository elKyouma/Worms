#include <box2d/b2_body.h>
#include <box2d/b2_body.h>
#include <box2d/b2_circle_shape.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_world.h>
#include <SDL2/SDL_image.h>
#include "Core/Physics/ColliderFactory.h"
#include "Core/Physics/ContactManager.h"
#include "ExceptionHandling/SDL_Exception.h"
#include "Game/Weapon/Projectile.h"
#include "Terminal/Terminal.h"

Projectile::Projectile( float posX, float posY, float vX, float vY ) : startPosX( posX ), startPosY( posY ), startVelX( vX ), startVelY( vY )
{
}

void Projectile::Update()
{
	if ( timer.Measure() > params.explosionOffset && params.explosionOffset != 0 )
		createSensor = true;

	if ( createSensor )
	{
		createSensor = false;
		explosionSound->Play();

		world->GetComponent<RigidBody>( objectId ).body->SetAwake( true );
		sensorInfo.id = objectId;
		sensorInfo.tag = PhysicsTag::DESTRUCTION_FIELD;
		b2CircleShape shape;
		shape.m_radius = params.explosionRadius;
		fixture = ColliderFactory::Get().CreateTriggerFixture( collider->GetBody(), &shape, sensorInfo );
		GameObject::objsToDelete.emplace_back( this );
	}
}

void Projectile::CleanUp()
{
	world->GetComponent<Sprite>( objectId ).texture = nullptr;
	ColliderFactory::Get().GetPhysicsWorld()->DestroyBody( world->GetComponent<RigidBody>( objectId ).body );
	GameObject::CleanUp();
}

void Projectile::onCollision( b2Contact* constact )
{
	ContactManager::Get().DeleteEvent( objectId, CollisionType::BEGIN, std::bind( &Projectile::onCollision, this, std::placeholders::_1 ) );
	collisionSound->Play();
	if ( params.explosionOffset == 0 )
		createSensor = true;

}

void Projectile::Initialise( SDL_Renderer* newRenderer, World* newWorld )
{
	GameObject::Initialise( newRenderer, newWorld );

	timer.Reset();

	world->AddComponent<Position>( objectId, { startPosX, startPosY } );

	Sprite& spriteComponent = world->AddComponent<Sprite>( objectId, { texture } );

	world->AddComponent<Rotation>( objectId, { 0 } );
	auto rigidBody = &world->AddComponent<RigidBody>( objectId );

	physicsInfo.id = objectId;
	physicsInfo.tag = PhysicsTag::BULLET;

	b2CircleShape shape;
	shape.m_radius = 0.1f;
	collider = std::make_unique<Collider>( ColliderFactory::Get().CreateDynamicBody( &shape, { startPosX, startPosY }, physicsInfo, reinterpret_cast<uintptr_t>(&params) ) );
	collider->SetContinuous( true );
	collider->SetVelocity( b2Vec2( startVelX * params.maxSpeed, startVelY * params.maxSpeed ) );

	rigidBody->body = collider->GetBody();
	rigidBody->body->SetGravityScale( params.gravityScale );

	ContactManager::Get().AddEvent( objectId, CollisionType::BEGIN, std::bind( &Projectile::onCollision, this, std::placeholders::_1 ) );

	camera->ChangeTarget( objectId );
}