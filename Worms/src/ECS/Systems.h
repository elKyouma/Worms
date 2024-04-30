#pragma once
#include "../Camera.h"
#include "Components.h"
#include "System.h"

class Movement : public System
{
public:
	Movement( ComponentManager& componentManager ) : System( componentManager )
	{
		systemSignature.set( componentManager.GetComponentId<Position>(), true );
		systemSignature.set( componentManager.GetComponentId<Motion>(), true );
	}

	virtual void Update() override
	{
		auto& positions = componentManager.GetComponentArray<Position>();
		auto& motions = componentManager.GetComponentArray<Motion>();
		for ( EntityId ent : subscribed )
		{
			positions.GetData( ent ).x += motions.GetData( ent ).v_x;
			positions.GetData( ent ).y += motions.GetData( ent ).v_y;
		}
	}
};

class SpriteRenderer : public System
{
public:
	SpriteRenderer( ComponentManager& componentManager, SDL_Renderer* renderer, Camera& camera )
		: System( componentManager ),
		renderer( renderer ),
		camera( camera )
	{
		systemSignature.set( componentManager.GetComponentId<Position>(), true );
		systemSignature.set( componentManager.GetComponentId<Sprite>(), true );
	}

	virtual void Render() override
	{
		auto& positions = componentManager.GetComponentArray<Position>();
		auto& sprites = componentManager.GetComponentArray<Sprite>();
		for ( EntityId ent : subscribed )
		{
			SDL_Point size;
			SDL_QueryTexture( sprites.GetData( ent ).texture, NULL, NULL, &size.x, &size.y );
			SDL_Rect spriteImage;
			spriteImage.x = 0;
			spriteImage.y = 0;
			spriteImage.w = size.x;
			spriteImage.h = size.y;

			SDL_Rect destination;
			destination.x = static_cast<int>(100.0 * (positions.GetData( ent ).x - camera.X()));
			destination.y = static_cast<int>(100.0 * (-positions.GetData( ent ).y + camera.Y()));
			destination.w = static_cast<int>(size.x * camera.Zoom());
			destination.h = static_cast<int>(size.y * camera.Zoom());

			SDL_RenderDrawRect( renderer, &spriteImage );
			SDL_RenderCopy( renderer, sprites.GetData( ent ).texture, &spriteImage, &destination );
		}
	}

private:
	SDL_Renderer* renderer;
	Camera& camera;
};