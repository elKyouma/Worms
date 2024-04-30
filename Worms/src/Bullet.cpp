#include "Bullet.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "ExceptionHandling/SDL_Exception.h"

Bullet::Bullet( SDL_Renderer* renderer, World* world ) : world(world)
{
	bulletId = world->CreateEntity();
	world->AddComponent<Position>(bulletId);

	Sprite& spriteComponent = world->AddComponent<Sprite>(bulletId);
	spriteComponent.texture = IMG_LoadTexture(renderer, "placeHolderBullet.png");
	SDL_CHECK(spriteComponent.texture);

	rigidBody = &world->AddComponent<RigidBody>(bulletId);
}

Bullet::~Bullet()
{
	SDL_DestroyTexture(world->GetComponent<Sprite>(bulletId).texture);
}

void Bullet::Update()
{

}
