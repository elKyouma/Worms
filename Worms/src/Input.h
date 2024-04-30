#pragma once
#include "SDL2/SDL.h"

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

private:
	float horizontal;
	float vertical;

	float camera_horizontal;
	float camera_vertical;
	Input() = default;

};