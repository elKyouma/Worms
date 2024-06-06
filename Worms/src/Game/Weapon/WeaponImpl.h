#pragma once
#include <string>

struct WeaponImpl
{
	std::string weaponTexturePath = "placeHolderWeapon.png";
	std::string projectileTexturePath = "placeHolderBullet.png";;
	std::string soundPath;
	float explosionOffset = 0;
	float explosionRadius = 1.f;
	float baseDamage = 40.f;
	float gravityScale = 1.f;
	float maxSpeed = 2.5f;
};