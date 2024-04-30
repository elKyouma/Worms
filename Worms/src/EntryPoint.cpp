#include <fstream>

#include <stdio.h> /* printf and fprintf */
#include "Game.h"
#include "Time.h"

/* Sets constants */
#define WIDTH 800
#define HEIGHT 600

int WinMain( int argc, char** argv )
{
	std::unique_ptr<Game> game = std::make_unique<Game>();
	Time::Timer timer{};

	try
	{
		game->InitWindow( "Worms", 800, 600 );

		while ( game->IsRunning() )
		{
			Time::deltaTime = timer.Reset();
			game->HandleEvents();
			game->Update();
			game->Render();
		}

		game->Clean();
	}
	catch ( SDL_Exception& e )
	{
		std::ofstream logs{ "logs.txt" };
		logs << e.what() << std::endl;
		logs.close();
	}

	return 0;
}