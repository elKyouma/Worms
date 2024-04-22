#include <fstream>
#include <imgui.h>
#include <imgui_impl_sdlrenderer2.h>
#include <SDL2/SDL.h> /* macOS- and GNU/Linux-specific */
#include <stdio.h> /* printf and fprintf */
#include "ExceptionHandling/SDL_Exception.h"
#include "imgui_impl_sdl2.h"

/* Sets constants */
#define WIDTH 800
#define HEIGHT 600

int WinMain( int argc, char** argv )
{
	try
	{
		/* Initialises data */
		SDL_Window* window = NULL;
		SDL_Renderer* renderer = NULL;

		// Initialises the SDL video subsystem (as well as the events subsystem).
		SDL_CALL( SDL_Init( SDL_INIT_VIDEO ) != 0 );

		/* Creates a SDL window */
		window = SDL_CreateWindow( "SDL Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, 0 );
		SDL_CHECK( window );

		renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
		SDL_CHECK( renderer );

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

		// Setup Dear ImGui style
		ImGui::StyleColorsDark();

		// Setup Platform/Renderer backends
		ImGui_ImplSDL2_InitForSDLRenderer( window, renderer );
		ImGui_ImplSDLRenderer2_Init( renderer );

		bool quiting = false;
		while ( !quiting )
		{
			SDL_Event ev;
			while ( SDL_PollEvent( &ev ) )
			{
				ImGui_ImplSDL2_ProcessEvent( &ev );
				switch ( ev.type )
				{
				case SDL_QUIT:
					quiting = true;
					break;
				}
			}
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
			ImGui::Render();
			SDL_RenderSetScale( renderer, io.DisplayFramebufferScale.x, io.DisplayFramebufferScale.y );
			SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );
			SDL_RenderClear( renderer );
			ImGui_ImplSDLRenderer2_RenderDrawData( ImGui::GetDrawData() );
			SDL_RenderPresent( renderer );
		}

		/* Frees memory */
		ImGui_ImplSDLRenderer2_Shutdown();
		ImGui_ImplSDL2_Shutdown();
		SDL_DestroyWindow( window );
		SDL_DestroyRenderer( renderer );

		/* Shuts down all SDL subsystems */
		SDL_Quit();
	}
	catch ( SDL_Exception& e )
	{
		std::ofstream logs{ "logs.txt" };
		logs << e.what() << std::endl;
		logs.close();
	}

	return 0;
}