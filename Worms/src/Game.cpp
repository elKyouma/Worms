#include <imgui_impl_sdlrenderer2.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Game.h"
#include "imgui_impl_sdl2.h"

Game::Game()
{
	world = std::make_unique<World>();

}

void Game::InitWindow( const std::string& title, const int width, const int height )
{
	// Initialises the SDL video subsystem (as well as the events subsystem).
	SDL_CALL( SDL_Init( SDL_INIT_VIDEO ) != 0 );

	/* Creates a SDL window */
	window = SDL_CreateWindow( title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0 );
	SDL_CHECK( window );

	renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
	SDL_CHECK( renderer );

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

	isRunning = true;

	SDL_Surface* temp = IMG_Load( "worms.png" );
	if ( temp == NULL )
		printf( "IMG_Load: %s\n", IMG_GetError() );
	sprite.texture = SDL_CreateTextureFromSurface( renderer, temp );
	SDL_FreeSurface( temp );
}

void Game::Update()
{
	world->Update();
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
	SDL_SetRenderDrawColor( renderer, 0, 0, 255, 255 );

	/* Draw the selected image of the sprite at the right position */
	{
		/* Define the source rectangle for the BlitSurface */
		SDL_Point size;
		SDL_QueryTexture( sprite.texture, NULL, NULL, &size.x, &size.y );
		SDL_Rect spriteImage;
		spriteImage.x = 0;
		spriteImage.y = 0;
		spriteImage.w = size.x;
		spriteImage.h = size.y;

		SDL_RenderDrawRect( renderer, &spriteImage );
		SDL_RenderCopy( renderer, sprite.texture, &spriteImage, &spriteImage );
	}

	ImGui::Render();
	SDL_RenderSetScale( renderer, io->DisplayFramebufferScale.x, io->DisplayFramebufferScale.y );
	ImGui_ImplSDLRenderer2_RenderDrawData( ImGui::GetDrawData() );
	SDL_RenderPresent( renderer );
}

void Game::Clean()
{
	SDL_DestroyTexture( sprite.texture );
	ImGui_ImplSDLRenderer2_Shutdown();
	ImGui_ImplSDL2_Shutdown();

	SDL_DestroyWindow( window );
	SDL_DestroyRenderer( renderer );
	SDL_Quit();
}
