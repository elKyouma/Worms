#pragma once
#include "Core/Camera.h"
#include "Game/Components.h"
#include "ECS/System.h"

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

			SDL_Rect destination;
			destination.x = static_cast<int>(400 + 100.0 * (positions.GetData( ent ).x - camera.X()) - size.x / 2);
			destination.y = static_cast<int>(300 - 100.0 * (positions.GetData( ent ).y - camera.Y()) - size.y / 2);
			destination.w = static_cast<int>(size.x * camera.Zoom());
			destination.h = static_cast<int>(size.y * camera.Zoom());

			auto angle = componentManager.TryGetComponent<Rotation>( ent );
			if ( angle.has_value() )
				SDL_RenderCopyEx( renderer, sprites.GetData( ent ).texture, NULL, &destination, -angle.value().get().degree, NULL, SDL_RendererFlip::SDL_FLIP_NONE );
			else
				SDL_RenderCopy( renderer, sprites.GetData( ent ).texture, NULL, &destination );
		}
	}

private:
	SDL_Renderer* renderer;
	Camera& camera;
};

class PhysicsSynchronizer : public System
{
public:
	PhysicsSynchronizer ( ComponentManager& componentManager)
		: System( componentManager )
	{
		systemSignature.set( componentManager.GetComponentId<Position>(), true );
		systemSignature.set( componentManager.GetComponentId<RigidBody>(), true );
	}

	virtual void Update() override
	{
		auto& positions = componentManager.GetComponentArray<Position>();
		auto& rigidBody = componentManager.GetComponentArray<RigidBody>();
		for ( EntityId ent : subscribed )
		{
			positions.GetData( ent ).x = rigidBody.GetData( ent ).body->GetPosition().x;
			positions.GetData( ent ).y = rigidBody.GetData( ent ).body->GetPosition().y;
		}
	}
private:
};