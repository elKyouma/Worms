#pragma once

#include "Core/GameObject.h"
#include "Game/Components.h"

class FocusPoint : public GameObject
{
public:
	FocusPoint( SDL_Renderer* newRenderer, World* newWorld );
	void ChangeTarget( EntityId newTargetId ) { target->id = newTargetId; }
	const Position& GetPos() const { return *pos; };
	float Y() const { return pos->y; };
private:
	Position* pos;
	Follow* target;
};