#include "Game/Player/WormTeam.h"

void WormTeam::addWorm( Worm* worm )
{
	_worms.push_back( worm );
	if ( _worms.size() == 1 )
		_worms[0]->Activate();
}

void WormTeam::removeWorm( Worm* worm )
{
	_worms.erase( std::remove_if( _worms.begin(), _worms.end(),
				  [worm] ( Worm* current ) {return worm == current; } ) );
}

void WormTeam::changeActiveWorm()
{
	if ( _worms.empty() ) return;

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

void WormTeam::Update()
{
	for ( auto& worm : _worms )
		worm->Update();
}

WormTeam::~WormTeam() {
	for ( auto& worm : _worms )
		delete worm;
	_worms.clear();
}