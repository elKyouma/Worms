#include "Input.h"

void Input::UpdateInputsDown( const SDL_Event& ev )
{
	switch ( ev.key.keysym.scancode )
	{
	case SDL_SCANCODE_W: vertical = -1.f; break;
	case SDL_SCANCODE_S: vertical = 1.f; break;
	case SDL_SCANCODE_A: horizontal = -1.f; break;
	case SDL_SCANCODE_D: horizontal = 1.f; break;
	case SDL_SCANCODE_UP: camera_vertical = -1.f; break;
	case SDL_SCANCODE_DOWN: camera_vertical = 1.f; break;
	case SDL_SCANCODE_LEFT: camera_horizontal = -1.f; break;
	case SDL_SCANCODE_RIGHT: camera_horizontal = 1.f; break;

	}
}

void Input::UpdateInputsUp( const SDL_Event& ev )
{
	switch ( ev.key.keysym.scancode )
	{
	case SDL_SCANCODE_W:
	case SDL_SCANCODE_S:
		vertical = 0.f;
		break;
	case SDL_SCANCODE_A:
	case SDL_SCANCODE_D:
		horizontal = 0.f;
		break;
	case SDL_SCANCODE_UP:
	case SDL_SCANCODE_DOWN:
		Input::Get().camera_vertical = 0.f;
		break;
	case SDL_SCANCODE_LEFT:
	case SDL_SCANCODE_RIGHT:
		Input::Get().camera_horizontal = 0.f;
		break;
	}
}
