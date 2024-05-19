#pragma once

enum PhysicsTag
{
	NONE,
	BULLET,
	WORM,
	GROUNDED
};

struct PhysicsInfo
{
	PhysicsTag tag;
};

