#pragma once
#include <box2d/b2_world.h>
#include "Game/Player/WormTeam.h"

class WormManager
{
public:
	WormManager( SDL_Renderer* renderer, World* world, b2World* physicsWorld, Camera& camera );
	WormManager( const WormManager& ) = delete;
	WormManager( WormManager&& ) = delete;

	void createTeam( int size );
	void deleteTeam( WormTeam* team );
	EntityId GetActiveWormId() { return _teams[_activeTeam]->getActiveWorm(); }
	void Update();

	~WormManager();
private:
	void ChangeTeam();
	void ChangeActiveWorm();

	std::vector<WormTeam*> _teams;
	int _activeTeam = 0;

	SDL_Renderer* _renderer;
	World* _world;
	b2World* physicsWorld;
	Camera& camera;
};