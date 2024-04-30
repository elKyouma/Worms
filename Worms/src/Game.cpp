#include <imgui_impl_sdlrenderer2.h>
#include <SDL2/SDL.h>
#include "Game.h"
#include "imgui_impl_sdl2.h"
#include "Input.h"

Game::Game() {}

void Game::InitWindow( const std::string& title, const int width, const int height )
{
	InitSDL( title, width, height );
	InitImGui();

	isRunning = true;
	world = std::make_unique<World>( renderer );
	world->RegisterComponent<Position>();
	world->RegisterComponent<Sprite>();
	world->RegisterComponent<Motion>();
	world->RegisterSystem<Movement>();
	world->RegisterSystem<SpriteRenderer>( renderer, camera );

	worm = std::make_unique<Worm>( renderer, world.get() );
	map = std::make_unique<Map>( renderer, world.get() );
}

void Game::InitSDL( const std::string& title, const int width, const int height )
{
	// Initialises the SDL video subsystem (as well as the events subsystem).
	SDL_CALL( SDL_Init( SDL_INIT_VIDEO ) != 0 );

	/* Creates a SDL window */
	window = SDL_CreateWindow( title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0 );
	SDL_CHECK( window );

	renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
	SDL_CHECK( renderer );
}


void Game::InitImGui()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	io = &ImGui::GetIO(); (void)*io;
	io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io->ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();

	// Setup Platform/Renderer backends
	ImGui_ImplSDL2_InitForSDLRenderer( window, renderer );
	ImGui_ImplSDLRenderer2_Init( renderer );
}

void Game::Update()
{
	world->Update();
	worm->Update();//Should add some WormManager in the future
	camera.Update();
}

void Game::HandleInputs( const SDL_Event& ev )
{
	switch ( ev.key.keysym.scancode )
	{
	case SDL_SCANCODE_W: Input::Get().vertical = -1.f; break;
	case SDL_SCANCODE_S: Input::Get().vertical = 1.f; break;
	case SDL_SCANCODE_A: Input::Get().horizontal = -1.f; break;
	case SDL_SCANCODE_D: Input::Get().horizontal = 1.f; break;
	case SDL_SCANCODE_UP: Input::Get().camera_vertical = -1.f; break;
	case SDL_SCANCODE_DOWN: Input::Get().camera_vertical = 1.f; break;
	case SDL_SCANCODE_LEFT: Input::Get().camera_horizontal = -1.f; break;
	case SDL_SCANCODE_RIGHT: Input::Get().camera_horizontal = 1.f; break;

	}
}

void Game::ResetInputs( const SDL_Event& ev )
{
	switch ( ev.key.keysym.scancode )
	{
	case SDL_SCANCODE_W:
	case SDL_SCANCODE_S:
		Input::Get().vertical = 0.f;
		break;
	case SDL_SCANCODE_A:
	case SDL_SCANCODE_D:
		Input::Get().horizontal = 0.f;
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

void Game::HandleEvents()
{
	SDL_Event ev;
	while ( SDL_PollEvent( &ev ) )
	{
		ImGui_ImplSDL2_ProcessEvent( &ev );
		switch ( ev.type )
		{
		case SDL_QUIT:
			isRunning = false;
			break;
		case SDL_KEYUP:
			ResetInputs( ev );
			break;
		case SDL_KEYDOWN:
			HandleInputs( ev );
			break;
		}

	}
}

void Game::Render()
{
	// Start the Dear ImGui frame
	ImGui_ImplSDLRenderer2_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();

	ImGui::BeginMainMenuBar();
	ImGui::MenuItem( "Game" );
	ImGui::MenuItem( "Editors" );
	ImGui::MenuItem( "Debug" );
	ImGui::EndMainMenuBar();

	// Rendering
	SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );
	SDL_RenderClear( renderer );

	world->Render();
	ImGui::Render();
	SDL_RenderSetScale( renderer, io->DisplayFramebufferScale.x, io->DisplayFramebufferScale.y );
	ImGui_ImplSDLRenderer2_RenderDrawData( ImGui::GetDrawData() );
	SDL_RenderPresent( renderer );
}

void Game::Clean()
{
	ImGui_ImplSDLRenderer2_Shutdown();
	ImGui_ImplSDL2_Shutdown();

	SDL_DestroyWindow( window );
	SDL_DestroyRenderer( renderer );
	SDL_Quit();
}

