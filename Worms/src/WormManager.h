#pragma once
#include "Worm.h"

class WormManager
{
public:
	WormManager( SDL_Renderer* renderer, World* world );
	WormManager( const WormManager& ) = delete;
	WormManager( WormManager&& ) = delete;

	void createTeam(int size);
	void deleteTeam( WormTeam* team);
	void Update();

	~WormManager();
private:
	void ChangeTeam();
	void ChangeActiveWorm();
	SDL_Renderer* _renderer = NULL;
	World* _world = NULL;
	std::vector<WormTeam*> _teams;
	int _activeTeam = 0;
};