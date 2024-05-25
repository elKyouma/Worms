#include "core/Physics/Collider.h"
#include "core/Physics/ContactManager.h"

void Collider::SetParent( Position& parent, const b2Vec2 offset )
{
	this->parent = &parent;
	this->offset = offset;
}

void Collider::SetPosition( Position pos )
{
	this->pos = pos;
}

void Collider::AddOnColliderEnter( std::function<void( b2Contact* )> callback ) const
{
	ContactManager::Get().AddEvent( physicsInfo.id, CollisionType::BEGIN, callback );
}

void Collider::AddOnCollider( std::function<void( b2Contact* )> callback ) const
{
	ContactManager::Get().AddEvent( physicsInfo.id, CollisionType::WHILE, callback );
}

void Collider::AddOnColliderExit( std::function<void( b2Contact* )> callback ) const
{
	ContactManager::Get().AddEvent( physicsInfo.id, CollisionType::END, callback );
}

void Collider::RemoveOnColliderEnter( std::function<void( b2Contact* )> callback ) const
{
	ContactManager::Get().DeleteEvent( physicsInfo.id, CollisionType::BEGIN, callback );
}

void Collider::RemoveOnCollider( std::function<void( b2Contact* )> callback ) const
{
	ContactManager::Get().DeleteEvent( physicsInfo.id, CollisionType::WHILE, callback );
}

void Collider::RemoveOnColliderExit( std::function<void( b2Contact* )> callback ) const
{
	ContactManager::Get().DeleteEvent( physicsInfo.id, CollisionType::END, callback );
}

void Collider::ClearOnColliderEnter() const
{
	ContactManager::Get().ClearEvent( physicsInfo.id, CollisionType::BEGIN );
}

void Collider::ClearOnCollider() const
{
	ContactManager::Get().ClearEvent( physicsInfo.id, CollisionType::WHILE );
}

void Collider::ClearOnColliderExit() const
{
	ContactManager::Get().ClearEvent( physicsInfo.id, CollisionType::END );
}

void Collider::FreezeRotation()
{
	body->SetFixedRotation( true );
}

void Collider::SetContinuous( bool isContinuous )
{
	body->SetBullet( isContinuous );
}

void Collider::ApplyForce( b2Vec2 force )
{
	body->ApplyForceToCenter( force, true );
}

void Collider::SetVelocity( b2Vec2 velocity )
{
	body->ApplyLinearImpulseToCenter( velocity, true );
}

b2Body* Collider::GetBody()
{
	return body;
}


void Collider::Update()
{
	if ( parent != NULL && body->GetType() )
	{
		pos.x = parent->x + offset.x;
		pos.y = parent->y + offset.y;
		body->SetTransform( { pos.x, pos.y }, 0 );
	}
}

Collider::Collider( b2Body* body, b2Vec2 offset, Position* parent )
{
	this->body = body;
	this->parent = parent;
	this->offset = offset;
	Update();
}
