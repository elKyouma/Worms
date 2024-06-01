#pragma once
#include <box2d/b2_contact.h>
#include <optional>
#include "ECS/ECS_Types.h"

enum PhysicsTag
{
	NONE,
	BULLET,
	DESTRUCTION_FIELD,
	WORM,
	GROUNDED,
	MAP
};

struct PhysicsInfo
{
	PhysicsTag tag;
	EntityId id;
};

std::optional<EntityId> GetEntityWithTag( b2Contact* contact, PhysicsTag tag );