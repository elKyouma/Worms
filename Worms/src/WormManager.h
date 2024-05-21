#pragma once
#include <box2d/b2_world.h>
#include "Worm.h"
#include "WormTeam.h"

class WormManager
{
public:
	WormManager( SDL_Renderer* renderer, World* world, b2World* physicsWorld );
	WormManager( const WormManager& ) = delete;
	WormManager( WormManager&& ) = delete;

	void createTeam( int size );
	void deleteTeam( WormTeam* team );
	void Update();

	~WormManager();
private:
	void ChangeTeam();
	void ChangeActiveWorm();
	SDL_Renderer* _renderer = NULL;
	World* _world = NULL;
	b2World* physicsWorld = NULL;
	std::vector<WormTeam*> _teams;
	int _activeTeam = 0;
};