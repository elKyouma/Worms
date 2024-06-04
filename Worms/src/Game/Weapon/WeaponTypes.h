#pragma once
#include "WeaponImpl.h"

struct Grenade : public WeaponImpl
{
	Grenade()
	{
		weaponTexturePath = "grenade.png";
		projectilleTexturePath = "grenade.png";
		explosionOffset = 2.f;
	}
};

struct Bazooka : public WeaponImpl
{
	Bazooka()
	{
		weaponTexturePath = "grenade.png";
		projectilleTexturePath = "placeHolderBullet.png";
		gravityScale = 0.1f;
		maxSpeed = 3.f;
		explosionRadius = 0.5f;
	}
};