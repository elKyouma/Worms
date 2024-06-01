#pragma once

#include "Core/GameObject.h"
#include "Game/Components.h"

class Camera : public GameObject
{
public:
	float& X() { return pos->x; };
	float X() const { return pos->x; };
	float& Y() { return pos->y; };
	float Y() const { return pos->y; };
	float Zoom() { return zoom; };

	void Initialise( SDL_Renderer* newRenderer, World* newWorld ) override;
	void Update() override;
	void ChangeX( float deltaX ) { pos->x += deltaX; }
	void ChangeY( float deltaY ) { pos->y += deltaY; }
	void ChangeZoom( float delta ) { zoom += delta; }
	void ChangeTarget( EntityId newTargetId ) { target->id = newTargetId; }
private:
	float zoom = 1.f;
	bool inputs_enabled = true;
	Position* pos;
	Follow* target;

	static constexpr float CAMERA_SPEED = 2.f;
};

