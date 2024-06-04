#include <box2d/b2_circle_shape.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_world.h>
#include <SDL2/SDL_image.h>
#include "Core/Physics/ColliderFactory.h"
#include "Core/Physics/ContactManager.h"
#include "ExceptionHandling/SDL_Exception.h"
#include "Game/Weapon/Projectille.h"
#include "Terminal/Terminal.h"

Projectille::Projectille( float posX, float posY, float vX, float vY ) : startPosX( posX ), startPosY( posY ), startVelX( vX ), startVelY( vY )
{
}

void Projectille::Update()
{
	if ( destroyNextFrame )
	{
		destroyNextFrame = false;
		collider->GetBody()->DestroyFixture( fixture );
		GameObject::objsToDelete.emplace_back( this );
		return;
	}
	if ( timer.Measure() > explosionOffset && explosionOffset != 0 )
		createSensor = true;

	if ( createSensor )
	{
		createSensor = false;
		destroyNextFrame = true;

		rigidBody->body->SetAwake( true );
		sensorInfo.id = objectId;
		sensorInfo.tag = PhysicsTag::DESTRUCTION_FIELD;
		b2CircleShape shape;
		shape.m_radius = explosionRadius;
		fixture = ColliderFactory::Get().CreateTriggerFixture( collider->GetBody(), &shape, sensorInfo );
	}
}

void Projectille::CleanUp()
{
	ColliderFactory::Get().GetPhysicsWorld()->DestroyBody( rigidBody->body );
	SDL_DestroyTexture( world->GetComponent<Sprite>( objectId ).texture );
}

void Projectille::onCollision( b2Contact* constact )
{
	ContactManager::Get().DeleteEvent( objectId, CollisionType::BEGIN, std::bind( &Projectille::onCollision, this, std::placeholders::_1 ) );
	if( explosionOffset == 0 )
		createSensor = true;
	
}

void Projectille::Initialise( SDL_Renderer* newRenderer, World* newWorld )
{
	GameObject::Initialise( newRenderer, newWorld );

	timer.Reset();

	position = &world->AddComponent<Position>( objectId, { startPosX, startPosY } );

	Sprite& spriteComponent = world->AddComponent<Sprite>( objectId );
	spriteComponent.texture = IMG_LoadTexture( renderer, texturePath.c_str() );
	SDL_CHECK( spriteComponent.texture );

	world->AddComponent<Rotation>( objectId, { 0 } );
	rigidBody = &world->AddComponent<RigidBody>( objectId );

	physicsInfo.id = objectId;
	physicsInfo.tag = PhysicsTag::BULLET;

	b2CircleShape shape;
	shape.m_radius = 0.1f;
	collider = std::make_unique<Collider>( ColliderFactory::Get().CreateDynamicBody( &shape, { position->x, position->y }, physicsInfo ) );
	collider->SetContinuous( true );
	collider->SetVelocity( b2Vec2( startVelX * maxSpeed, startVelY * maxSpeed ) );

	rigidBody->body = collider->GetBody();
	rigidBody->body->SetGravityScale( gravityScale );

	ContactManager::Get().AddEvent( objectId, CollisionType::BEGIN, std::bind( &Projectille::onCollision, this, std::placeholders::_1 ) );

}