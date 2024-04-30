#include "Camera.h"
#include "Input.h"

void Camera::Update()
{
	if ( !inputs_enabled ) return;

	ChangeX( Input::Get().CameraHorizontal() * 0.2 );
	ChangeY( Input::Get().CameraVertical() * 0.2 );
}
