#pragma once
#include <box2d/b2_contact.h>
#include <box2d/b2_fixture.h>
#include <functional>
#include "box2d/b2_world.h"
#include "ECS/ECS_Types.h"
#include "Game/Components.h"
#include "Game/Tags.h"

class ColliderFactory;

class Collider
{
public:
	void SetParent( Position& pos, const b2Vec2 offset );
	void SetPosition( Position pos );

	void AddOnColliderEnter( std::function<void( b2Contact* )> callback ) const;
	void AddOnCollider( std::function<void( b2Contact* )> callback ) const;
	void AddOnColliderExit( std::function<void( b2Contact* )> callback ) const;

	void RemoveOnColliderEnter( std::function<void( b2Contact* )> callback ) const;
	void RemoveOnCollider( std::function<void( b2Contact* )> callback ) const;
	void RemoveOnColliderExit( std::function<void( b2Contact* )> callback ) const;

	void ClearOnColliderEnter() const;
	void ClearOnCollider() const;
	void ClearOnColliderExit() const;

	void FreezeRotation();

	void SetContinuous( bool isContinuous );
	void ApplyForce( b2Vec2 force );
	void SetVelocity( b2Vec2 velocity );

	b2Body* GetBody();

	void Update();

private:
	PhysicsInfo physicsInfo;
	b2Body* body;
	Position* parent = NULL;

	b2Vec2 offset;
	Position pos;

	friend ColliderFactory;
	Collider( b2Body*, b2Vec2 offset = {}, Position* parent = NULL );;
};

