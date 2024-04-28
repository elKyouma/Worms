#include "pch.h"
#include "Components.h"
#include "World.cpp"

class WorldTest : public ::testing::Test
{

};

TEST_F( WorldTest, CreateObjectAndThenDeleteIt )
{
	World world{};
	EntityId e1 = world.CreateEntity();
	world.DestroyEntity( e1 );
}

TEST_F( WorldTest, CreateObjectAndUseSystem )
{
	World world{};
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