#include "pch.h"
#include "SystemManager.cpp"
#include "Systems.h"

class TestSystemManager : public ::testing::Test
{
protected:
	void RegisterComponents()
	{
		componentManager.RegisterComponent<Position>();
		componentManager.RegisterComponent<Motion>();
	}

protected:
	ComponentManager componentManager{};
};

TEST_F( TestSystemManager, RegisterSystem_WhenCompoenntsUnregistered )
{
	SystemManager systemManager{ componentManager };
	EXPECT_THROW( { systemManager.RegisterSystem<Movement>(); }, ECS_Exception );
}

TEST_F( TestSystemManager, RegisterSystem )
{
	RegisterComponents();
	SystemManager systemManager{ componentManager };
	systemManager.RegisterSystem<Movement>();
}

TEST_F( TestSystemManager, RegisterAndUpdateSystem )
{
	RegisterComponents();

	auto& pos = componentManager.GetComponentArray<Position>().AddData( 0 );
	auto& motion = componentManager.GetComponentArray<Motion>().AddData( 0 );

	pos.x = 1.0f;
	motion.v_x = 2.0f;
	motion.v_y = 4.0f;

	SystemManager systemManager{ componentManager };
	systemManager.RegisterSystem<Movement>();
	systemManager.OnSignatureChange( 0, 3 );
	systemManager.Update();

	EXPECT_FLOAT_EQ( pos.x, 3.0f );
	EXPECT_FLOAT_EQ( pos.y, 4.0f );
}


TEST_F( TestSystemManager, WrongSignature )
{
	RegisterComponents();

	auto& positions = componentManager.GetComponentArray<Position>();
	positions.AddData( 0 );
	positions.AddData( 2 );


	auto& motions = componentManager.GetComponentArray<Motion>();
	motions.AddData( 0 );
	motions.AddData( 1 );

	SystemManager systemManager{ componentManager };
	systemManager.RegisterSystem<Movement>();
	systemManager.OnSignatureChange( 0, 3 );
	systemManager.OnSignatureChange( 1, 2 );
	systemManager.OnSignatureChange( 2, 1 );
	systemManager.Update();
}


