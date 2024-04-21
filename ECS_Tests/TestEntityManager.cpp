#include "pch.h"
#include "EntityManager.cpp"
#include "EntityManager.h"

class TestEntityManager : public ::testing::Test
{

};

TEST_F( TestEntityManager, CreateEntity )
{
	EntityManager manager;
	EntityId id1 = manager.CreateEntity();
	EntityId id2 = manager.CreateEntity();
	EntityId id3 = manager.CreateEntity();

	EXPECT_EQ( id1, 0 );
	EXPECT_EQ( id2, 1 );
	EXPECT_EQ( id3, 2 );

	EXPECT_EQ( manager.GetAmountOfAvailableEntities(), MAX_ENTITIES - 3 );
}

TEST_F( TestEntityManager, AvailableEntitiesHasRightSize )
{
	EntityManager manager;
	EntityId id1 = manager.CreateEntity();
	EntityId id2 = manager.CreateEntity();
	EntityId id3 = manager.CreateEntity();

	EXPECT_EQ( id1, 0 );
	EXPECT_EQ( id2, 1 );
	EXPECT_EQ( id3, 2 );

	EXPECT_EQ( manager.GetAmountOfAvailableEntities(), MAX_ENTITIES - 3 );

	manager.DestroyEntity( id2 );
	EXPECT_EQ( manager.GetAmountOfAvailableEntities(), MAX_ENTITIES - 2 );

}