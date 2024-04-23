#include <vector>
#include "ComponentManager.h"

void ComponentManager::AddComponents( EntityId ent, Signature sign )
{
	for ( uint8_t i = 0; i < registeredComponents; i++ )
		if ( sign.test( i ) )
			components[i]->AddDataNoReturn( ent );
}

void ComponentManager::RemoveAllComponents( EntityId ent, Signature sign )
{
	for ( uint8_t i = 0; i < registeredComponents; i++ )
		if ( sign.test( i ) )
			components[i]->EraseData( ent );
}

std::vector<std::string> ComponentManager::GetRegisteredComponents()
{
	std::vector<std::string> result{};
	for ( auto it = typeToComponentId.begin(); it != typeToComponentId.end(); it++ )
		result.push_back( it->first );

	return result;
}

ComponentManager::~ComponentManager()
{
	for ( int i = 0; i < registeredComponents; i++ )
		delete components[i];
}
