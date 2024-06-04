#include "WeaponManager.h"

void WeaponManager::Initialise()
{
	weapons.push_back( new Grenade );
	weapons.push_back( new Bazooka );
	for ( WeaponImpl* params : weapons )
	{
		textures.insert( { params->weaponTexturePath, IMG_LoadTexture( renderer, params->weaponTexturePath.c_str() ) } );
		sounds.insert( { params->soundPath, Sound( params->soundPath ) } );
	}
	weapon->SetParams( *weapons[0] );
	weapon->SetTexture( textures[weapons[0]->weaponTexturePath] );

}

void WeaponManager::Update()
{
	
}

WeaponManager::~WeaponManager()
{
	for ( auto& [name, texture] : textures )
	{
		SDL_DestroyTexture( texture );
	}
	sounds.clear();
	for ( WeaponImpl* weapon : weapons )
	{
		delete weapon;
	}
}
