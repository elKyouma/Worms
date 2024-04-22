#pragma once
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
		}
		for ( EntityId ent : subscribed )
		{
			positions.GetData( ent ).y += motions.GetData( ent ).v_y;
		}
	}
};