#include "WormManager.h"
#include "Input.h"

WormManager::WormManager( SDL_Renderer* renderer, World* world )
	: _renderer(renderer), _world(world), _teams() {}

void WormManager::createTeam( int size )
{
	WormTeam* newTeam = new WormTeam;
	for ( int i = 0; i < size; i++ ) {
		newTeam->addWorm( new Worm( _renderer, _world ));
	}
	_teams.push_back( newTeam );
}

void WormManager::deleteTeam( WormTeam* team )
{
	_teams.erase( std::remove_if( _teams.begin(), _teams.end(),
				  [team] ( WormTeam* current ) {return team == current; } ) );
}

void WormManager::Update()
{
	if (Input::Get().ChangeWorm())
		ChangeActiveWorm();
	if (Input::Get().ChangeTeam())
		ChangeTeam();

	_teams[_activeTeam]->Update();
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

void WormManager::ChangeTeam()
{
	if ( _teams.empty() ) return;

	_activeTeam += 1;
	if ( _activeTeam == _teams.size() )
		_activeTeam = 0;
}

void WormManager::ChangeActiveWorm()
{
	if ( _teams.empty() ) return;
	_teams[_activeTeam]->changeActiveWorm();
}
