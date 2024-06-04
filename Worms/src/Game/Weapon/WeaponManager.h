#pragma once
#include <map>
#include <vector>
#include <SDL2/SDL_image.h>
#include "WeaponImpl.h"
#include "Core/Audio/Sound.h"

class WeaponManager
{ 
public:
	void Initialise();
	void Update();
private:
	std::vector<WeaponImpl> weapons;
	std::map<std::string, Sound> sounds;
	std::map<std::string, SDL_Texture*> textures;

};

