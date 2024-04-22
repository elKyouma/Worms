#include <vector>
#include "ComponentManager.h"

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
