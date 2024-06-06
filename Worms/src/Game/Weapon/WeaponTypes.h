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
		weaponTexturePath = "bazooka.png";
		projectilleTexturePath = "placeHolderBullet.png";
		gravityScale = 0.5f;
		maxSpeed = 5.f;
		explosionRadius = 0.2f;
	}
};