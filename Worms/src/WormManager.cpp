#include "WormManager.h"

WormManager::WormManager( SDL_Renderer* renderer, World* world )
	: _renderer(renderer), _world(world), _teams() {}

void WormManager::addTeam( int size )
{
	WormTeam* new_team = new WormTeam;
	for ( int i = 0; i < size; i++ ) {
		new_team->addWorm( new Worm( _renderer, _world ));
	}
}

WormManager::~WormManager() {
	if ( !_teams.empty() )
	{
		for ( auto& team : _teams )
		{
			delete team;
			team = nullptr;
		}
		_teams.clear();
	}
}