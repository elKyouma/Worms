#include "WeaponManager.h"
//#include "Terminal/Terminal.h"

void WeaponManager::Initialise()
{
	weapons.push_back( new Grenade );
	weapons.push_back( new Bazooka );
	for ( WeaponImpl* params : weapons )
	{
		textures.insert( { params->weaponTexturePath, IMG_LoadTexture( renderer, params->weaponTexturePath.c_str() ) } );
		textures.insert( { params->projectileTexturePath, IMG_LoadTexture( renderer, params->projectileTexturePath.c_str() ) } );
		sounds.insert( { params->explosionSound, new Sound( params->explosionSound ) } );
		sounds.insert( { params->collisionSound, new Sound( params->collisionSound ) } );
		sounds.insert( { params->shootingSound, new Sound( params->shootingSound ) } );
	}
	weapon->SetParams( *weapons[0] );
	weapon->SetTexture( textures[weapons[0]->weaponTexturePath] );

}

void WeaponManager::Update()
{
	currentWeapon += Input::Get().ChangeWeapon();

	if ( currentWeapon < 0 )
		currentWeapon = static_cast<int>(weapons.size()) - 1;
	if ( currentWeapon > weapons.size() - 1 )
		currentWeapon = 0;

	weapon->SetParams( *weapons[currentWeapon] );
	weapon->SetTexture( textures[weapons[currentWeapon]->weaponTexturePath] );
	weapon->SetProjectileTexture( textures[weapons[currentWeapon]->projectileTexturePath] );
	weapon->SetExplosionSound( sounds[weapons[currentWeapon]->explosionSound] );
	weapon->SetShootingSound( sounds[weapons[currentWeapon]->shootingSound] );
	weapon->SetCollisionSound( sounds[weapons[currentWeapon]->collisionSound] );

	//Terminal::Get().Log( std::to_string( currentWeapon ), LogLevel::INFO );
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
