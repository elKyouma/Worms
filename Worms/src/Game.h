#pragma once
#include <imgui.h>
#include <SDL2/SDL.h> /* macOS- and GNU/Linux-specific */
#include <string>
#include "ExceptionHandling/SDL_Exception.h"

class Game
{
public:
	void InitWindow( const std::string& title, const int width, const int height );
	void Update();
	void HandleEvents();
	void Render();
	void Clean();

	inline bool IsRunning() { return isRunning; }
private:
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	ImGuiIO* io = NULL;

	bool isRunning = false;
};

