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

