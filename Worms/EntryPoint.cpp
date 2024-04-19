#include <fstream>
#include <SDL2/SDL.h> /* macOS- and GNU/Linux-specific */
#include <stdio.h> /* printf and fprintf */
#include "SDL_Exception.h"

/* Sets constants */
#define WIDTH 800
#define HEIGHT 600
#define DELAY 3000

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

		bool quiting = false;
		while ( !quiting )
		{
			SDL_Event ev;
			while ( SDL_PollEvent( &ev ) )
			{
				switch ( ev.type )
				{
				case SDL_QUIT:
					quiting = true;
					break;
				}
			}
		}

		/* Frees memory */
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