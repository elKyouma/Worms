#pragma once
class Camera
{
public:
	float X() { return x; };
	float Y() { return y; };
	float Zoom() { return zoom; };

	void Update();
	void ChangeX( float deltaX ) { x += deltaX; }
	void ChangeY( float deltaY ) { y += deltaY; }
	void ChangeZoom( float delta ) { zoom += delta; }
private:
	float x = 0.f;
	float y = 0.f;
	float zoom = 1.f;
	bool inputs_enabled = true;

	static constexpr float CAMERA_SPEED = 200.f;
};

