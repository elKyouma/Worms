#pragma once
#include "WeaponImpl.h"

struct Grenade : public WeaponImpl
{
	Grenade()
	{
		weaponTexturePath = "grenade.png";
		projectileTexturePath = "grenade.png";
		shootingSound = "throw_granade.wav";
		explosionSound = "big_explosion.wav";
		explosionOffset = 2.f;
	}
};

struct Bazooka : public WeaponImpl
{
	Bazooka()
	{
		weaponTexturePath = "bazooka.png";
		projectileTexturePath = "placeHolderBullet.png";
		explosionSound = "small_explosion.wav";
		shootingSound = "shoot_bazooka.wav";
		gravityScale = 0.5f;
		maxSpeed = 5.f;
		explosionRadius = 0.2f;
	}
};