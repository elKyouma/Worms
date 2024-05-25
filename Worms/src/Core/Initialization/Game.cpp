#include <imgui_impl_sdlrenderer2.h>
#include <SDL2/SDL.h>
#include "Core/Physics/ContactManager.h"
#include "Game.h"
#include "imgui_impl_sdl2.h"
#include "Core/Input.h"
#include "Core/Time.h"

Game::Game() {}

void Game::InitWindow( const std::string& title, const int width, const int height )
{
	InitSDL( title, width, height );
	InitImGui();

	isRunning = true;
	world = std::make_unique<World>( renderer );
	world->RegisterComponent<Position>();
	world->RegisterComponent<Rotation>();
	world->RegisterComponent<Health>();
	world->RegisterComponent<Sprite>();
	world->RegisterComponent<Motion>();
	world->RegisterComponent<RigidBody>();
	world->RegisterSystem<Movement>();
	world->RegisterSystem<SpriteRenderer>( renderer, camera );

	physicsWorld = std::make_unique<b2World>( b2Vec2( 0, -9.811 ) );
	b2DebugDraw = std::make_unique<b2ColliderDraw>( renderer, camera );
	physicsWorld->SetDebugDraw( b2DebugDraw.get() );
	physicsWorld->SetContactListener( &ContactManager::Get() );

	wormManager = std::make_unique<WormManager>( renderer, world.get(), physicsWorld.get() );
	wormManager->createTeam( 4 );
	wormManager->createTeam( 4 );
	bullet = std::make_unique<Projectille>( renderer, world.get(), physicsWorld.get() );
	map = std::make_unique<Map>( renderer, world.get(), physicsWorld.get() );
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
	physicsWorld->Step( Time::deltaTime, 8, 3 );
	wormManager->Update();
	camera.Update();
	map->Update( renderer );

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
			Input::Get().UpdateInputsUp( ev );
			break;
		case SDL_KEYDOWN:
			Input::Get().UpdateInputsDown( ev );
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
	if ( ImGui::BeginMenu( "Debug" ) )
	{
		ImGui::Checkbox( "Toggle colliders", &toggleColliders );
		ImGui::EndMenu();
	}
	ImGui::EndMainMenuBar();

	// Rendering
	SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );
	SDL_RenderClear( renderer );

	world->Render();
	bullet->Update();

	ImGui::Render();
	SDL_RenderSetScale( renderer, io->DisplayFramebufferScale.x, io->DisplayFramebufferScale.y );
	ImGui_ImplSDLRenderer2_RenderDrawData( ImGui::GetDrawData() );
	if ( toggleColliders )
		physicsWorld->DebugDraw();
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

