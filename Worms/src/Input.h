#pragma once
#include "SDL2/SDL.h"
#include "WormManager.h"

class Input
{
public:
	Input( const Input& ) = delete;
	Input( Input&& ) = delete;

	static Input& Get()
	{
		static Input input{};
		return input;
	}

	void UpdateInputsDown( const SDL_Event& ev );
	void UpdateInputsUp( const SDL_Event& ev );

	float Horizontal() const { return horizontal; }
	float Vertical() const { return vertical; }

	float CameraHorizontal() const { return camera_horizontal; }
	float CameraVertical() const { return camera_vertical; }

	bool ChangeWorm() { return change_worm; }
	bool ChangeTeam() { return change_team; }

	//bool ChangeWorm() { if ( change_worm ) { change_worm = false; return true; } else return false; }
	//bool ChangeTeam() { if ( change_team ) { change_team = false; return true; } else return false; }

private:
	float horizontal;
	float vertical;

	float camera_horizontal;
	float camera_vertical;

	bool change_worm;
	bool change_team;
	Input() = default;

};