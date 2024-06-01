#include "Core/Camera.h"
#include "Core/Input.h"
#include "Core/Time.h"

void Camera::Initialise( SDL_Renderer* newRenderer, World* newWorld )
{
	GameObject::Initialise( newRenderer, newWorld );
	pos = &world->AddComponent<Position>( objectId, { 2, -1 } );
	target = &world->AddComponent<Follow>( objectId, { 3 } );

}

void Camera::Update()
{
	if ( !inputs_enabled ) return;

	ChangeX( Input::Get().CameraHorizontal() * static_cast<float>(Time::deltaTime) * CAMERA_SPEED );
	ChangeY( Input::Get().CameraVertical() * static_cast<float>(Time::deltaTime) * CAMERA_SPEED );
}