#pragma once
#include <map>
#include <vector>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include "Weapon.h"
#include "WeaponTypes.h"
#include "Core/Audio/Sound.h"

class WeaponManager
{ 
public:
	WeaponManager( SDL_Renderer* renderer,  Weapon* weapon) : renderer( renderer ), weapon(weapon) {}
	void Initialise();
	void Update();
	~WeaponManager();
private:
	SDL_Renderer* renderer;
	Weapon* weapon;
	std::vector<WeaponImpl *> weapons;
	std::map<std::string, Sound> sounds;
	std::map<std::string, SDL_Texture*> textures;

};

