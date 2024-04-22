#pragma once
#include <set>
#include "ComponentManager.h"
#include "ECS_Types.h"
class System
{
public:
	System( ComponentManager& componentManager ) : componentManager( componentManager ) {}
	virtual void Update() {};
	inline Signature GetSystemSignature() const { return systemSignature; }
	bool CheckIfSubscribed( EntityId ent ) const { return subscribed.find( ent ) != subscribed.end(); }
	void Subscribe( EntityId ent ) { subscribed.insert( ent ); }
	void Unsubscribe( EntityId ent ) { subscribed.erase( ent ); }

protected:
	Signature systemSignature;
	std::set<EntityId> subscribed;
	ComponentManager& componentManager;
};
