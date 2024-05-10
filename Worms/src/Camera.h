#pragma once
class Camera
{
public:
	float X() { return _x; };
	float Y() { return _y; };
	float Zoom() { return zoom; };

	void Update();
	void ChangePosition(float x, float y);
	void ChangeX( float deltaX ) { _x += deltaX; }
	void ChangeY( float deltaY ) { _y += deltaY; }
	void ChangeZoom( float delta ) { zoom += delta; }
private:
	float _x = 0.f;
	float _y = 0.f;
	float zoom = 1.f;
	bool inputs_enabled = true;

	static constexpr float CAMERA_SPEED = 2.f;
};

