#pragma once
#include <imgui.h>
#include <SDL2/SDL.h> /* macOS- and GNU/Linux-specific */
#include <string>
#include "ECS/Components.h"
#include "ECS/World.h"
#include "ExceptionHandling/SDL_Exception.h"

class Game
{
public:
	Game();
	void InitWindow( const std::string& title, const int width, const int height );
	void Update();
	void HandleEvents();
	void Render();
	void Clean();

	inline bool IsRunning() { return isRunning; }
private:
	void InitSDL( const std::string& title, const int width, const int height );
	void InitImGui();

	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	ImGuiIO* io = NULL;
	std::unique_ptr<World> world;
	bool isRunning = false;
};
