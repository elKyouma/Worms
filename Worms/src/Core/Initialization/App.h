#pragma once
#include <imgui.h>
#include <SDL2/SDL.h> /* macOS- and GNU/Linux-specific */
#include <string>
#include "box2d/b2_world.h"
#include "Core/Camera/Camera.h"
#include "Core/Physics/b2ColliderDraw.h"
#include "ECS/World.h"
#include "ExceptionHandling/SDL_Exception.h"
#include "Game/Components.h"
#include "Game/Map/Map.h"
#include "Game/Player/Worm.h"
#include "Game/Player/WormManager.h"
#include "Game/Weapon/Weapon.h"


class App
{
public:
	App();
	virtual void InitWindow( const std::string& title, const int width, const int height );
	virtual void Update();
	virtual void HandleEvents();
	virtual void Render();
	void PostRender();
	void PreRender();
	virtual void Clean();

	inline bool IsRunning() const { return isRunning; }

protected:
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	std::unique_ptr<World> world;
	std::unique_ptr<b2World> physicsWorld;
	std::unique_ptr<b2ColliderDraw> b2DebugDraw;

private:
	void InitSDL( const std::string& title, const int width, const int height );
	void InitImGui();
	ImGuiIO* io = 0;


	bool toggleColliders = false;
	bool isRunning = false;
};

