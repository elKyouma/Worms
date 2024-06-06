#include "Core/Camera.h"
#include "Core/Input.h"
#include "Core/Time.h"
#include "Terminal/Terminal.h"
#include "SDL2/SDL_image.h"
#include "ExceptionHandling/SDL_Exception.h"

double smoothstep( double x, double endPoint, double currentPoint)
{	
	int noTraceBarrier = 1.0;
	int maxTace = 5.0;
	int sign = (endPoint - currentPoint > 0) ? 1 : -1;
	if ( fabs( x ) < 1.0 ) return 0;
	x = std::clamp( (fabs( x ) - noTraceBarrier) / (maxTace - noTraceBarrier), 0.0, 0.2 );
	return x * x * (3 - 2 * x) * sign;
}

Position adjustPos( const Position& focusPos, const Position& currentPos)
{
	Position newPos{ 0,0 };
	double dx = focusPos.x - currentPos.x;
	double dy = focusPos.y - currentPos.y;
	newPos.x = smoothstep( dx, focusPos.x, currentPos.x);
	newPos.y = smoothstep( dy, focusPos.y, currentPos.y);
	return newPos;
}

FocusPoint::FocusPoint( SDL_Renderer* newRenderer, World* newWorld )
{
	GameObject::Initialise( newRenderer, newWorld );
	pos = &world->AddComponent<Position>( objectId, { 2, -1 } );
	target = &world->AddComponent<Follow>( objectId, { 3 } );
	Sprite& spriteComponent = world->AddComponent<Sprite>( objectId );
	spriteComponent.texture = IMG_LoadTexture( renderer, "placeHolderBullet.png" );
	SDL_CHECK( spriteComponent.texture );
}


void Camera::Initialise( SDL_Renderer* newRenderer, World* newWorld )
{
	GameObject::Initialise( newRenderer, newWorld );
	pos = &world->AddComponent<Position>( objectId, { 2, -1 } );
	focusPoint = std::make_unique<FocusPoint>(newRenderer, newWorld);
}

void Camera::Update()
{
	if ( inputs_enabled )
	{
		ChangeX( Input::Get().CameraHorizontal() * static_cast<float>(Time::deltaTime) * CAMERA_SPEED );
		ChangeY( Input::Get().CameraVertical() * static_cast<float>(Time::deltaTime) * CAMERA_SPEED );
		return;
	}
	ChangePos( adjustPos( focusPoint->GetPos(), *pos));
}