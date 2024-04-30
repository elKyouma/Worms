#include "Camera.h"
#include "Input.h"

void Camera::Update()
{
	if ( !inputs_enabled ) return;

	ChangeX( Input::Get().camera_horizontal * 0.02 );
	ChangeY( Input::Get().camera_vertical * 0.02 );
}
