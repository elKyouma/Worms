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

		/*
		* Initialises the SDL video subsystem (as well as the events subsystem).
		* Returns 0 on success or a negative error code on failure using SDL_GetError().
		*/
		SDL_CALL( SDL_Init( SDL_INIT_VIDEO ) != 0 );

		/* Creates a SDL window */
		window = SDL_CreateWindow( "SDL Example", /* Title of the SDL window */
								   SDL_WINDOWPOS_UNDEFINED, /* Position x of the window */
								   SDL_WINDOWPOS_UNDEFINED, /* Position y of the window */
								   WIDTH, /* Width of the window in pixels */
								   HEIGHT, /* Height of the window in pixels */
								   0 ); /* Additional flag(s) */

		SDL_CHECK( window );

		/* Pauses all SDL subsystems for a variable amount of milliseconds */
		SDL_Delay( DELAY );

		/* Frees memory */
		SDL_DestroyWindow( window );

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