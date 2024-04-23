#include "SystemManager.h"

void SystemManager::Update()
{
	for ( uint8_t i = 0; i < amountOfSystems; i++ )
		systems[i]->Update();
}

void SystemManager::OnSignatureChange( EntityId e, Signature signature )
{
	for ( uint8_t i = 0; i < amountOfSystems; i++ )
	{
		bool subscribed = systems[i]->CheckIfSubscribed( e );
		bool rightSignature = (systems[i]->GetSystemSignature() & signature) == systems[i]->GetSystemSignature();
		if ( !subscribed && rightSignature )
			systems[i]->Subscribe( e );
		else if ( subscribed && !rightSignature )
			systems[i]->Unsubscribe( e );
	}
}

void SystemManager::UnsubscribeEntity( EntityId e )
{
	for ( uint8_t i = 0; i < amountOfSystems; i++ )
		if ( systems[i]->CheckIfSubscribed( e ) )
			systems[i]->Unsubscribe( e );
}

SystemManager::~SystemManager()
{
	for ( uint8_t i = 0; i < amountOfSystems; i++ )
		delete systems[i];
}
