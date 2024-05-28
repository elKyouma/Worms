#include "pch.h"
#include "ComponentManager.cpp"
#include "ECS_Types.h"
#include "game/Components.h"

class TestComponentManager : public ::testing::Test
{

};

//ComponentArray<Position>;

TEST_F( TestComponentManager, RegisterComponentAndAccessTheData )
{
	ComponentManager manager{};
	manager.RegisterComponent<Position>();

	for ( int i = 0; i < 10; i++ )
		manager.AddComponent<Position>( i );

	Position& p = manager.GetComponent<Position>( 3 );
	p.x = 3.f;
	p.y = 8.f;
	EXPECT_FLOAT_EQ( manager.GetComponentArray<Position>().GetData( 3 ).x, 3.f );
	EXPECT_FLOAT_EQ( manager.GetComponentArray<Position>().GetDataAtIndex( 3 ).x, 3.f );
	EXPECT_FLOAT_EQ( manager.GetComponentArray<Position>().GetData( 3 ).y, 8.f );
	EXPECT_FLOAT_EQ( manager.GetComponentArray<Position>().GetDataAtIndex( 3 ).y, 8.f );
}

TEST_F( TestComponentManager, CheckRegisteredTypes )
{
	ComponentManager manager{};
	manager.RegisterComponent<Position>();
	auto vec = manager.GetRegisteredComponents();


	EXPECT_EQ( vec.size(), 1 );
	EXPECT_STREQ( vec[0].c_str(), "struct Position" );
	manager.RegisterComponent<Motion>();
	vec = manager.GetRegisteredComponents();
	EXPECT_EQ( vec.size(), 2 );
}

TEST_F( TestComponentManager, ComponentAlreadyRegistered )
{
	ComponentManager manager{};
	manager.RegisterComponent<Position>();
	EXPECT_THROW( { manager.RegisterComponent<Position>(); }, ECS_Exception );
}

TEST_F( TestComponentManager, UnregisteredComponent )
{
	ComponentManager manager{};
	EXPECT_THROW( { manager.GetComponentArray<Position>(); }, ECS_Exception );
}