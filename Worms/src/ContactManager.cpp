#include "ContactManager.h"
#include "Tags.h"

void ContactManager::BeginContact( b2Contact* contact )
{
	if ( contact->GetFixtureA()->GetUserData().pointer != 0 )
	{
		PhysicsInfo* info1 = (PhysicsInfo*)contact->GetFixtureA()->GetUserData().pointer;
		if ( beginEvents.contains( info1->id ) );
		{
			auto& evts = beginEvents[info1->id];
			for ( const auto& evt : evts )
				evt( contact );
		}
	}

	if ( contact->GetFixtureB()->GetUserData().pointer != 0 )
	{
		PhysicsInfo* info2 = (PhysicsInfo*)contact->GetFixtureB()->GetUserData().pointer;
		if ( beginEvents.contains( info2->id ) );
		{
			auto& evts = beginEvents[info2->id];
			for ( const auto& evt : evts )
				evt( contact );
		}
	}
}

void ContactManager::EndContact( b2Contact* contact )
{
	if ( contact->GetFixtureA()->GetUserData().pointer != 0 )
	{
		PhysicsInfo* info1 = (PhysicsInfo*)contact->GetFixtureA()->GetUserData().pointer;
		if ( beginEvents.contains( info1->id ) );
		{
			auto& evts = endEvents[info1->id];
			for ( const auto& evt : evts )
				evt( contact );
		}
	}

	if ( contact->GetFixtureB()->GetUserData().pointer != 0 )
	{
		PhysicsInfo* info2 = (PhysicsInfo*)contact->GetFixtureB()->GetUserData().pointer;
		if ( beginEvents.contains( info2->id ) );
		{
			auto& evts = endEvents[info2->id];
			for ( const auto& evt : evts )
				evt( contact );
		}
	}
}

void ContactManager::AddEvent( const EntityId entId, const CollisionType type, std::function<void( b2Contact* )> evt )
{
	auto& events = GetEvents( type );
	auto iterator = events.find( entId );
	if ( iterator == events.end() )
	{
		events[entId].push_back( evt );
	}
}

void ContactManager::DeleteEvent( const EntityId entId, const CollisionType type, std::function<void( b2Contact* )> evt )
{
	auto& events = GetEvents( type );
	auto iterator = events.find( entId );
	if ( iterator == events.end() )
	{
		//Throw error
	}
	else
	{
		auto& vec = events[entId];
		//vec.erase( std::remove( vec.begin(), vec.end(), evt ) );
	}
}

EventMap& ContactManager::GetEvents( const CollisionType type )
{
	switch ( type )
	{
	case CollisionType::BEGIN:
		return beginEvents;
	case CollisionType::WHILE:
		return updateEvents;
	case CollisionType::END:
		return endEvents;
	}
}
