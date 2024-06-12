#include "Game/Player/WormTeam.h"

void WormTeam::addWorm( Worm* worm )
{
	_worms.push_back( worm );
	if ( _worms.size() == 1 )
		_worms[0]->Activate();
}

void WormTeam::removeWorm( Worm* worm )
{
	bool needToUpdate = false;
	if ( worm == _worms[_activeWorm] )
		needToUpdate = true;

	_worms.erase( std::remove_if( _worms.begin(), _worms.end(),
				  [worm] ( Worm* current ) {return worm == current; } ) );

	if ( needToUpdate )
		changeActiveWorm();
}

void WormTeam::changeActiveWorm()
{
	if ( _worms.empty() ) return;

	if ( _worms.size() > _activeWorm )
		_worms[_activeWorm]->Disactivate();
	_activeWorm++;
	if ( _activeWorm == _worms.size() )
		_activeWorm = 0;

	_worms[_activeWorm]->Activate();
}

EntityId WormTeam::getActiveWorm()
{
	return _worms[_activeWorm]->GetId();
}

int WormTeam::Size() const
{
	return _worms.size();
}

void WormTeam::RenderHealthBars() {
	for ( auto worm : _worms )
	{
		worm->Render();
	}
}

void WormTeam::Update()
{
	for ( auto& worm : _worms )
		worm->Update( _wormsToDelete );
	for ( auto worm : _wormsToDelete )
	{
		worm->CleanUp();
		removeWorm( worm );
	}
	_wormsToDelete.clear();
}

WormTeam::~WormTeam() {
	for ( auto& worm : _worms )
		delete worm;
	_worms.clear();
}