#pragma once
#include "WeaponImpl.h"

struct Grenade : public WeaponImpl
{
	Grenade()
	{
		weaponTexturePath = "grenade.png";
		projectileTexturePath = "grenade.png";
		explosionOffset = 2.f;
	}
};

struct Bazooka : public WeaponImpl
{
	Bazooka()
	{
		weaponTexturePath = "bazooka.png";
		projectileTexturePath = "placeHolderBullet.png";
		gravityScale = 0.5f;
		maxSpeed = 5.f;
		explosionRadius = 0.2f;
	}
};