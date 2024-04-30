#include <SDL2/SDL.h>
#include "ExceptionHandling/SDL_Exception.h"
#include "Input.h"
#include "Time.h"
#include "Utils.h"
#include "Worm.h"

Worm::Worm( SDL_Renderer* renderer, World* world ) : world( world )
{
	wormId = world->CreateEntity();
	world->AddComponent<Position>( wormId );
	Sprite& spriteComponent = world->AddComponent<Sprite>( wormId );
	motion = &world->AddComponent<Motion>( wormId );

	spriteComponent.texture = IMG_LoadTexture( renderer, "worms.png" );
	SDL_CHECK( spriteComponent.texture );
}

Worm::~Worm()
{
	SDL_DestroyTexture( world->GetComponent<Sprite>( wormId ).texture );
}

void Worm::Update()
{
	//Add input and delta by using singletons
	motion->v_y = Input::Get().Vertical() * Time::deltaTime * WORM_SPEED;
	motion->v_x = Input::Get().Horizontal() * Time::deltaTime * WORM_SPEED;
}