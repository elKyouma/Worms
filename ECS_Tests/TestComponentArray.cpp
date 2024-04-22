#include "pch.h"
#include <assert.h>
#include "ComponentArray.h"
#include "Components.h"

class TestComponentArray : public ::testing::Test
{
protected:
	void AddComponentsWithUniquePos( ComponentArray<Position>& components, const int amountOfComponents )
	{
		for ( int i = 0; i < amountOfComponents; i++ )
			components.AddData( i );

		for ( int i = 0; i < amountOfComponents; i++ )
			components.SetData( i, { 0.f, (float)i } );
	}
};

TEST_F( TestComponentArray, CreatePositionComponent ) {
	ComponentArray<Position> components{};
	components.AddData( 2 );
	auto& data = components.GetData( 2 );

	EXPECT_FLOAT_EQ( data.x, 0.0f );
	EXPECT_FLOAT_EQ( data.y, 0.0f );
}

TEST_F( TestComponentArray, UseTheSameComponent ) {
	ComponentArray<Position> components{};
	components.AddData( 1 );
	components.AddData( 2 );

	auto& data = components.GetData( 1 );

	data.x = 1.0f;
	data.y = 2.0f;

	EXPECT_FLOAT_EQ( data.x, 1.0f );
	EXPECT_FLOAT_EQ( data.y, 2.0f );

	components.SetData( 2, data );

	EXPECT_FLOAT_EQ( data.x, 1.0f );
	EXPECT_FLOAT_EQ( data.y, 2.0f );
}

TEST_F( TestComponentArray, ValidateMemoryPositioning ) {
	ComponentArray<Position> components{};
	const int amountOfComponents = 10;
	AddComponentsWithUniquePos( components, amountOfComponents );

	for ( int i = 0; i < amountOfComponents; i++ )
		EXPECT_FLOAT_EQ( components.GetData( i ).y, (float)i );

}

TEST_F( TestComponentArray, ValidateEraseComponentMemoryPositioning ) {
	ComponentArray<Position> components{};
	const int amountOfComponents = 10;
	AddComponentsWithUniquePos( components, amountOfComponents );

	components.EraseData( 5 );

	for ( int i = 0; i < amountOfComponents - 1; i++ )
	{
		if ( i == 5 )
		{
			EXPECT_FLOAT_EQ( components.GetDataAtIndex( i ).y, amountOfComponents - 1.f );
			continue;
		}
		EXPECT_FLOAT_EQ( components.GetData( i ).y, (float)i );
	}
}

TEST_F( TestComponentArray, ValidateEraseComponentThatDoesntExist ) {
	ComponentArray<Position> components{};
	const int amountOfComponents = 10;
	AddComponentsWithUniquePos( components, amountOfComponents );

	EXPECT_THROW( { components.EraseData( 12 ); }, ECS_Exception );

}

TEST_F( TestComponentArray, SetDataToComponentThatDoesntExist ) {
	ComponentArray<Position> components{};
	const int amountOfComponents = 10;
	AddComponentsWithUniquePos( components, amountOfComponents );

	EXPECT_THROW( { components.SetData( 12, Position{1.0f, 2.0f} ); }, ECS_Exception );

}

TEST_F( TestComponentArray, SetDataWorksProperly ) {
	ComponentArray<Position> components{};
	const int amountOfComponents = 10;
	AddComponentsWithUniquePos( components, amountOfComponents );

	components.SetData( 5, components.GetData( 8 ) );

	for ( int i = 0; i < amountOfComponents - 1; i++ )
	{
		if ( i == 5 )
		{
			EXPECT_FLOAT_EQ( components.GetData( i ).y, 8 );
			continue;
		}
		EXPECT_FLOAT_EQ( components.GetData( i ).y, (float)i );
	}
}

