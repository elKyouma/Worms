#include <box2d/b2_circle_shape.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_world.h>
#include <SDL2/SDL_image.h>
#include "Core/Physics/ColliderFactory.h"
#include "ExceptionHandling/SDL_Exception.h"
#include "Game/Weapon/Projectille.h"

Projectille::Projectille( SDL_Renderer* newRenderer, World* newWorld )
{
	GameObject::Initialise( newRenderer, newWorld );
}

Projectille::~Projectille()
{
	SDL_DestroyTexture( world->GetComponent<Sprite>( objectId ).texture );
}

void Projectille::Update()
{
}

void Projectille::Initialise( float posX, float posY, float vX, float vY )
{
	position = &world->AddComponent<Position>( objectId, { posX, posY } );

	Sprite& spriteComponent = world->AddComponent<Sprite>( objectId );
	spriteComponent.texture = IMG_LoadTexture( renderer, "placeHolderBullet.png" );
	SDL_CHECK( spriteComponent.texture );

	rotation = &world->AddComponent<Rotation>( objectId, { 0 } );

	rigidBody = &world->AddComponent<RigidBody>( objectId );

	physicsInfo.id = GetId();
	physicsInfo.tag = PhysicsTag::BULLET;

	b2CircleShape shape;
	shape.m_radius = 0.1;
	collider = std::make_unique<Collider>( ColliderFactory::Get().CreateDynamicBody( &shape, { position->x, position->y }, physicsInfo ) );
	collider->SetContinuous( true );
	collider->SetVelocity( b2Vec2( vX, vY ) );
	rigidBody->body = collider->GetBody();
}