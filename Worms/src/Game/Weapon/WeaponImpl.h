#pragma once
#include <string>

struct WeaponImpl
{
	std::string weaponTexturePath = "placeHolderWeapon.png";
	std::string projectileTexturePath = "placeHolderBullet.png";;
	std::string explosionSound = "jump.wav";
	std::string collisionSound = "jump.wav";
	std::string shootingSound = "jump.wav";

	float explosionOffset = 0;
	float explosionRadius = 1.f;
	float baseDamage = 40.f;
	float gravityScale = 1.f;
	float maxSpeed = 2.5f;
};