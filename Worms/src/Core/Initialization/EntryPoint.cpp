#include <fstream>

#include <stdio.h> /* printf and fprintf */
#include "Core/Time.h"
#include "Game.h"
#include "Terminal/Terminal.h"

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
	catch ( std::exception& e )
	{
		Terminal::Get().Log( e.what(), LogLevel::ERROR );
	}

	return 0;
}