#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_world.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Bullet.h"
#include "ExceptionHandling/SDL_Exception.h"

Bullet::Bullet( SDL_Renderer* renderer, World* world, b2World* physicsWorld ) : world( world )
{
	bulletId = world->CreateEntity();
	position = &world->AddComponent<Position>( bulletId );

	Sprite& spriteComponent = world->AddComponent<Sprite>( bulletId );
	spriteComponent.texture = IMG_LoadTexture( renderer, "placeHolderBullet.png" );
	SDL_CHECK( spriteComponent.texture );

	rigidBody = &world->AddComponent<RigidBody>( bulletId );


	static b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.angularDamping = 10;
	bodyDef.position = { position->x, position->y };
	rigidBody->body = physicsWorld->CreateBody( &bodyDef );

	static b2FixtureDef fixtureDef;

	static b2PolygonShape collider;
	collider.SetAsBox( 0.2, 0.2 );

	fixtureDef.shape = &collider;
	fixtureDef.density = 1;
	fixtureDef.friction = 1;

	rigidBody->body->CreateFixture( &fixtureDef );
	rigidBody->body->ApplyLinearImpulse( { 0.5, 0.4 }, { position->x, position->y }, true );
}

Bullet::~Bullet()
{
	SDL_DestroyTexture( world->GetComponent<Sprite>( bulletId ).texture );
}

void Bullet::Update()
{
	position->x = rigidBody->body->GetPosition().x;
	position->y = rigidBody->body->GetPosition().y;
}
