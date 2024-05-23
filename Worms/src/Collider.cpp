#include "Collider.h"
#include "ContactManager.h"

Collider::Collider( b2World* physicsWorld, PhysicsInfo physicsInfo, b2Shape* shape, bool isTrigger ) : physicsInfo( physicsInfo )
{
	bodyDef.type = b2_kinematicBody;
	bodyDef.fixedRotation = true;
	bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(this);
	body = physicsWorld->CreateBody( &bodyDef );

	fixtureDef.shape = shape;
	fixtureDef.isSensor = isTrigger;
	fixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(&physicsInfo);
	body->CreateFixture( &fixtureDef );
}

void Collider::SetParent( Position& parent, const b2Vec2 offset )
{
	this->parent = &parent;
	this->offset = offset;
}

void Collider::SetPosition( Position pos )
{
	this->pos = pos;
}

void Collider::OnColliderEnter( std::function<void( b2Contact* )> callback )
{
	ContactManager::Get().AddEvent( physicsInfo.id, CollisionType::BEGIN, callback );
}

void Collider::OnCollider( std::function<void( b2Contact* )> callback )
{
	ContactManager::Get().AddEvent( physicsInfo.id, CollisionType::WHILE, callback );
}

void Collider::OnColliderExit( std::function<void( b2Contact* )> callback )
{
	ContactManager::Get().AddEvent( physicsInfo.id, CollisionType::END, callback );
}

void Collider::Update()
{
	if ( parent != NULL )
	{
		pos.x = parent->x + offset.x;
		pos.y = parent->y + offset.y;
		body->SetTransform( { pos.x, pos.y }, 0 );
	}
}
