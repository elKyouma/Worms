#pragma once
#include "ECS/ECS_Types.h"

enum PhysicsTag
{
	NONE,
	BULLET,
	WORM,
	GROUNDED,
	MAP
};

struct PhysicsInfo
{
	PhysicsTag tag;
	EntityId id;
};

