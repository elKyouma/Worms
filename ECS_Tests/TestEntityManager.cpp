#include "pch.h"
#include "EntityManager.cpp"
#include "EntityManager.h"

class TestEntityManager : public ::testing::Test
{
public:
	virtual void SetUp() override
	{
		id1 = manager.CreateEntity();
		id2 = manager.CreateEntity();
		id3 = manager.CreateEntity();
	}
protected:
	EntityManager manager;
	EntityId id1;
	EntityId id2;
	EntityId id3;
};

TEST_F( TestEntityManager, CreateEntity )
{
	EXPECT_EQ( id1, 0 );
	EXPECT_EQ( id2, 1 );
	EXPECT_EQ( id3, 2 );

	EXPECT_EQ( manager.GetAmountOfAvailableEntities(), MAX_ENTITIES - 3 );
}

TEST_F( TestEntityManager, AvailableEntitiesHasRightSize )
{
	EXPECT_EQ( manager.GetAmountOfAvailableEntities(), MAX_ENTITIES - 3 );

	manager.DestroyEntity( id2 );
	EXPECT_EQ( manager.GetAmountOfAvailableEntities(), MAX_ENTITIES - 2 );

}

TEST_F( TestEntityManager, AddingComponentsToSignatures )
{
	manager.AddToSignature( id1, 1 );
	manager.AddToSignature( id1, 3 );
	EXPECT_EQ( manager.GetSignature( id1 ).to_ulong(), 10 );

	manager.AddToSignature( id2, 2 );
	manager.AddToSignature( id2, 5 );
	EXPECT_EQ( manager.GetSignature( id2 ).to_ulong(), 36 );
}

TEST_F( TestEntityManager, DeletingComponentFromSignature )
{
	manager.AddToSignature( id1, 1 );
	manager.AddToSignature( id1, 3 );
	EXPECT_EQ( manager.GetSignature( id1 ).to_ulong(), 10 );

	manager.DeleteFromSignature( id1, 1 );
	EXPECT_EQ( manager.GetSignature( id1 ).to_ulong(), 8 );
	manager.DeleteFromSignature( id1, 3 );
	EXPECT_EQ( manager.GetSignature( id1 ).to_ulong(), 0 );
}

TEST_F( TestEntityManager, SetGetSignature )
{
	manager.AddToSignature( id1, 1 );
	manager.AddToSignature( id1, 3 );
	manager.SetSignature( id2, manager.GetSignature( id1 ) );

	EXPECT_EQ( manager.GetSignature( id1 ).to_ulong(), 10 );
	EXPECT_EQ( manager.GetSignature( id2 ).to_ulong(), 10 );
}

