#include <box2d/b2_circle_shape.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_world.h>
#include <SDL2/SDL_image.h>
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


	static b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.angularDamping = 10;
	bodyDef.position = { position->x, position->y };
	bodyDef.bullet = true;
	rigidBody->body = physicsWorld->CreateBody( &bodyDef );

	static b2FixtureDef fixtureDef;

	static b2CircleShape collider;
	collider.m_radius = 0.1;

	fixtureDef.shape = &collider;
	fixtureDef.density = 1;
	fixtureDef.friction = 1;

	rigidBody->body->CreateFixture( &fixtureDef );
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
