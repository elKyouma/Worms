#include "Core/Camera.h"
#include "Core/Input.h"
#include "Core/Time.h"

void Camera::Update()
{
	if ( !inputs_enabled ) return;

	ChangeX( Input::Get().CameraHorizontal() * Time::deltaTime * CAMERA_SPEED );
	ChangeY( Input::Get().CameraVertical() * Time::deltaTime * CAMERA_SPEED );
}

void Camera::ChangePosition( float x, float y )
{
	_x = x;
	_y = y;
}
