#pragma once
#include <imgui.h>
#include <SDL2/SDL.h> /* macOS- and GNU/Linux-specific */
#include <string>
#include "box2d/b2_world.h"
#include "Core/Camera.h"
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
	void InitWindow( const std::string& title, const int width, const int height );
	void Update();
	void HandleEvents();
	void Render();
	void Clean();

	inline bool IsRunning() const { return isRunning; }
private:
	void InitSDL( const std::string& title, const int width, const int height );
	void InitImGui();

	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	ImGuiIO* io = 0;
	std::unique_ptr<World> world;
	std::unique_ptr<b2World> physicsWorld;
	std::unique_ptr<Map> map;
	std::unique_ptr<WormManager> wormManager;
	std::unique_ptr<b2ColliderDraw> b2DebugDraw;
	std::unique_ptr<Weapon> weapon;
	std::unique_ptr<Camera> camera;

	bool toggleColliders = false;
	bool isRunning = false;
};

