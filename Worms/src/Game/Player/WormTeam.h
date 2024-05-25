#pragma once
#include "Game/Player/Worm.h"

class WormTeam
{
public:
	void addWorm( Worm* worm );
	void removeWorm( Worm* worm );
	void changeActiveWorm();
	Worm* getActiveWorm();
	int Size() const;
	void Update();

	~WormTeam();
private:
	std::vector<Worm*> _worms;
	int _activeWorm = 0;
};