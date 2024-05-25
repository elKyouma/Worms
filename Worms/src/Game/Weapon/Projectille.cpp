#include <box2d/b2_circle_shape.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_world.h>
#include <SDL2/SDL_image.h>
#include "Core/Physics/ColliderFactory.h"
#include "ExceptionHandling/SDL_Exception.h"
#include "Game/Weapon/Projectille.h"

Projectille::Projectille( SDL_Renderer* newRenderer, World* newWorld, b2World* physicsWorld )
{
	Initialise( newRenderer, newWorld );
	position = &world->AddComponent<Position>( objectId, { 0, 2 } );
	rotation = &world->AddComponent<Rotation>( objectId, { 0 } );

	Sprite& spriteComponent = world->AddComponent<Sprite>( objectId );
	spriteComponent.texture = IMG_LoadTexture( renderer, "placeHolderBullet.png" );
	SDL_CHECK( spriteComponent.texture );

	rigidBody = &world->AddComponent<RigidBody>( objectId );

	b2CircleShape shape;
	shape.m_radius = 0.1;
	collider = std::make_unique<Collider>( ColliderFactory::Get().CreateDynamic( &shape, { position->x, position->y } ) );
	collider->SetContinuous( true );
	rigidBody->body = collider->GetBody();
}

Projectille::~Projectille()
{
	SDL_DestroyTexture( world->GetComponent<Sprite>( objectId ).texture );
}

void Projectille::Update()
{
	position->x = rigidBody->body->GetPosition().x;
	position->y = rigidBody->body->GetPosition().y;
	rotation->degree = rigidBody->body->GetAngle() * 180 / M_PI;
}
