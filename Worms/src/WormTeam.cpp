#include "WormTeam.h"

void WormTeam::addWorm( Worm* worm )
{
	_worms.push_back( worm );
}

void WormTeam::removeWorm( Worm* worm )
{
	_worms.erase( std::remove_if( _worms.begin(), _worms.end(),
				  [worm] ( Worm* current ) {return worm == current; } ) );
}

void WormTeam::changeActiveWorm()
{
	if ( _worms.empty() ) return;

	_activeWorm += 1;
	if ( _activeWorm == _worms.size() )
		_activeWorm = 0;
}

Worm* WormTeam::getActiveWorm()
{
	return _worms[_activeWorm];
}

int WormTeam::Size() const
{
	return _worms.size();
}

void WormTeam::Update()
{
	_worms[_activeWorm]->Update();
}

WormTeam::~WormTeam() {
	for ( auto& worm : _worms )
		delete worm;
	_worms.clear();
}