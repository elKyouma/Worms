#pragma once
#include "ECS/Components.h"
#include "ECS/Systems.h"
#include "ECS/World.h"

class Worm
{
public:
	Worm( SDL_Renderer* renderer, World* world );
	~Worm();
	void Update();

private:
	EntityId wormId;
	Motion* motion;
	World* world;

	static constexpr float WORM_SPEED = 2.f;
};

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
