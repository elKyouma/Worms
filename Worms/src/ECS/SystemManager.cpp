#include "SystemManager.h"

void SystemManager::Update()
{
	for ( auto sys : systems )
		sys->Update();
}

void SystemManager::OnSignatureChange( EntityId e, Signature signature )
{
	for ( uint8_t i = 0; i < amountOfSystems; i++ )
	{
		bool subscribed = systems[i]->CheckIfSubscribed( e );
		bool rightSignature = (systems[i]->GetSystemSignature() & signature) == signature;
		if ( !subscribed && rightSignature )
			systems[i]->Subscribe( e );
		else if ( subscribed && !rightSignature )
			systems[i]->Unsubscribe( e );
	}
}

SystemManager::~SystemManager()
{
	for ( uint8_t i = 0; i < amountOfSystems; i++ )
		delete systems[i];
}
