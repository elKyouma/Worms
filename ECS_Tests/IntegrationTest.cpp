#include "pch.h"
#include "game/Components.h"
#include "game/Systems.h"
#include "World.cpp"

class WorldTest : public ::testing::Test
{

};

TEST_F( WorldTest, CreateObjectAndThenDeleteIt )
{
	SDL_Renderer* renderer = SDL_CreateRenderer( SDL_CreateWindow( "", 0, 0, 0, 0, 0 ), 0, 0 );
	World world{ renderer };
	EntityId e1 = world.CreateEntity();
	world.DestroyEntity( e1 );
}

TEST_F( WorldTest, TryGetComponentThatDoesntExist )
{
	SDL_Renderer* renderer = SDL_CreateRenderer( SDL_CreateWindow( "", 0, 0, 0, 0, 0 ), 0, 0 );
	World world{ renderer };
	world.RegisterComponent<Position>();
	auto comp = world.TryGetComponent<Position>( 4 );
	EXPECT_FALSE( comp.has_value() );
}


TEST_F( WorldTest, CreateObjectAndUseSystem )
{
	SDL_Renderer* renderer = SDL_CreateRenderer( SDL_CreateWindow( "", 0, 0, 0, 0, 0 ), 0, 0 );
	World world{ renderer };
	world.RegisterComponent<Position>();
	world.RegisterComponent<Motion>();
	world.RegisterSystem<Movement>();
	EntityId e1 = world.CreateEntity();
	EntityId e2 = world.CreateEntity();
	world.AddComponent<Position>( e1 );
	world.AddComponent<Position>( e2 );
	world.AddComponent<Motion>( e1 ).v_y = -9;
	world.AddComponent<Motion>( e2 ).v_x = -9;
	world.Update();
	EXPECT_EQ( world.GetComponent<Position>( e1 ).x, 0 );
	EXPECT_EQ( world.GetComponent<Position>( e1 ).y, -9 );
	EXPECT_EQ( world.GetComponent<Position>( e2 ).x, -9 );
	EXPECT_EQ( world.GetComponent<Position>( e2 ).y, 0 );
}