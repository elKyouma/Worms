#pragma once
#include "Worm.h"

class WormManager
{
public:
	WormManager( SDL_Renderer* renderer, World* world );
	WormManager( const WormManager& ) = delete;
	WormManager( WormManager&& ) = delete;

	void addTeam(int size);

	~WormManager();
private:
	SDL_Renderer* _renderer = NULL;
	World* _world = NULL;
	std::vector<WormTeam*> _teams;
	WormTeam* _activeTeam = nullptr;
};