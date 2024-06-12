#pragma once
#include "Game/Player/Worm.h"

class WormTeam
{
	friend class Worm;
public:
	void addWorm( Worm* worm );
	void removeWorm( Worm* worm );
	void changeActiveWorm();
	EntityId getActiveWorm();
	int Size() const;
	void Update();
	void RenderHealthBars();

	~WormTeam();
private:
	std::vector<Worm*> _worms;
	std::vector<Worm*> _wormsToDelete;
	int _activeWorm = 0;
};