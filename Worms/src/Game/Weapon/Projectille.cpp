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

Projectille::~Projectille()
{
	ColliderFactory::Get().GetPhysicsWorld()->DestroyBody( rigidBody->body );
	SDL_DestroyTexture( world->GetComponent<Sprite>( objectId ).texture );
	world->DestroyEntity( objectId );
}

void Projectille::Update()
{
	if ( destroyNextFrame )
	{
		destroyNextFrame = false;
		collider->GetBody()->DestroyFixture( fixture );
		GameObject::objsToDelete.emplace_back( this );
	}

	if ( createSensor )
	{
		createSensor = false;
		destroyNextFrame = true;

		sensorInfo.id = objectId;
		sensorInfo.tag = PhysicsTag::DESTRUCTION_FIELD;
		b2CircleShape shape;
		shape.m_radius = 1.f;
		fixture = ColliderFactory::Get().CreateTriggerFixture( collider->GetBody(), &shape, sensorInfo );
	}
}

void Projectille::onCollision( b2Contact* constact )
{
	ContactManager::Get().DeleteEvent( objectId, CollisionType::BEGIN, std::bind( &Projectille::onCollision, this, std::placeholders::_1 ) );
	Terminal::Get().Log( "Destroyed bullet with id = " + std::to_string( objectId ), LogLevel::INFO );
	createSensor = true;

}

void Projectille::Initialise( SDL_Renderer* newRenderer, World* newWorld )
{
	GameObject::Initialise( newRenderer, newWorld );

	position = &world->AddComponent<Position>( objectId, { startPosX, startPosY } );

	Sprite& spriteComponent = world->AddComponent<Sprite>( objectId );
	spriteComponent.texture = IMG_LoadTexture( renderer, "placeHolderBullet.png" );
	SDL_CHECK( spriteComponent.texture );

	world->AddComponent<Rotation>( objectId, { 0 } );
	rigidBody = &world->AddComponent<RigidBody>( objectId );

	physicsInfo.id = objectId;
	physicsInfo.tag = PhysicsTag::BULLET;

	b2CircleShape shape;
	shape.m_radius = 0.1f;
	collider = std::make_unique<Collider>( ColliderFactory::Get().CreateDynamicBody( &shape, { position->x, position->y }, physicsInfo ) );
	collider->SetContinuous( true );
	collider->SetVelocity( b2Vec2( startVelX, startVelY ) );

	rigidBody->body = collider->GetBody();
	ContactManager::Get().AddEvent( objectId, CollisionType::BEGIN, std::bind( &Projectille::onCollision, this, std::placeholders::_1 ) );

}