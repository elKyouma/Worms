#include <fstream>

#include <stdio.h> /* printf and fprintf */
#include "Core/Initialization/App.h"
#include "Core/Time.h"
#include "Game/Game.h"
#include "Terminal/Terminal.h"

/* Sets constants */
#define WIDTH 800
#define HEIGHT 600

int WinMain( int argc, char** argv )
{
	std::unique_ptr<App> game = std::make_unique<Game>();
	Time::Timer timer{};

	try
	{
		game->InitWindow( "Worms", 800, 600 );

		while ( game->IsRunning() )
		{
			try
			{
				Time::deltaTime = timer.Reset();
				game->HandleEvents();
				game->Update();
				game->PreRender();
				game->Render();
				game->PostRender();
			}
			catch ( std::exception& e )
			{
				Terminal::Get().Log( e.what(), LogLevel::ERROR );
			}

		}

		game->Clean();
	}
	catch ( std::exception& e )
	{
		Terminal::Get().Log( e.what(), LogLevel::ERROR );
	}

	return 0;
}