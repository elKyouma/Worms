#include "Bullet.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "ExceptionHandling/SDL_Exception.h"
#include <box2d/b2_world.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_circle_shape.h>

Bullet::Bullet( SDL_Renderer* renderer, World* world, b2World* physicsWorld ) : world(world)
{
	bulletId = world->CreateEntity();
	position = &world->AddComponent<Position>(bulletId);

	Sprite& spriteComponent = world->AddComponent<Sprite>(bulletId);
	spriteComponent.texture = IMG_LoadTexture(renderer, "placeHolderBullet.png");
	SDL_CHECK(spriteComponent.texture);
	
	rigidBody = &world->AddComponent<RigidBody>(bulletId);


	static b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.linearVelocity = b2Vec2( 5, -1 );
	rigidBody->body = physicsWorld->CreateBody(&bodyDef);
	
	static b2FixtureDef fixtureDef;

	b2CircleShape collider;
	collider.m_radius = 0.2;
	collider.m_p.Set(0, 0);

	fixtureDef.shape = &collider;
	fixtureDef.density = 1;

	rigidBody->body->CreateFixture(&fixtureDef);

}

Bullet::~Bullet()
{
	SDL_DestroyTexture(world->GetComponent<Sprite>(bulletId).texture);
}

void Bullet::Update()
{
	position->x = rigidBody->body->GetPosition().x * 100;
	position->y = rigidBody->body->GetPosition().y * 100;
}
