#include "b2ColliderDraw.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600


void b2ColliderDraw::DrawSolidPolygon( const b2Vec2* vertices, int32 vertexCount, const b2Color& color )
{
	SDL_Point* points = new SDL_Point[vertexCount + 1];
	for ( int i = 0; i < vertexCount; i++ )
	{
		points[i].x = static_cast<int>(SCREEN_WIDTH / 2 + 100.0 * (vertices[i].x - camera.X()));
		points[i].y = static_cast<int>(SCREEN_HEIGHT / 2 - 100.0 * (vertices[i].y - camera.Y()));
	}
	points[vertexCount].x = static_cast<int>(SCREEN_WIDTH / 2 + 100.0 * (vertices[0].x - camera.X()));
	points[vertexCount].y = static_cast<int>(SCREEN_HEIGHT / 2 - 100.0 * (vertices[0].y - camera.Y()));

	SDL_SetRenderDrawColor( renderer, 0, 255, 0, 255 );

	SDL_RenderDrawLines( renderer, points, vertexCount + 1);

	delete[] points;

}

void b2ColliderDraw::DrawSegment( const b2Vec2& p1, const b2Vec2& p2, const b2Color& color )
{
	SDL_Point point1( SCREEN_WIDTH / 2 + 100.0 * (p1.x - camera.X()), SCREEN_HEIGHT / 2 - 100.0 * (p1.y - camera.Y()) );
	SDL_Point point2( SCREEN_WIDTH / 2 + 100.0 * (p2.x - camera.X()), SCREEN_HEIGHT / 2 - 100.0 * (p2.y - camera.Y()) );
	SDL_SetRenderDrawColor( renderer, 0, 255, 0, 255 );
	SDL_RenderDrawLine( renderer, point1.x, point1.y, point2.x, point2.y );

}
