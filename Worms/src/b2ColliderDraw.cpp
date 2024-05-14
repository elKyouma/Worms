#include "b2ColliderDraw.h"


void b2ColliderDraw::DrawPolygon( const b2Vec2* vertices, int32 vertexCount, const b2Color& color )
{
	SDL_Point* points = new SDL_Point[vertexCount];
	for ( int i = 0; i < vertexCount; i++ )
	{
		points[i].x = static_cast<int>(vertices[i].x);
		points[i].y = static_cast<int>(vertices[i].y);
	}
	SDL_RenderDrawLines( renderer, points, vertexCount );

	delete[] points;
}

void b2ColliderDraw::DrawSegment( const b2Vec2& p1, const b2Vec2& p2, const b2Color& color )
{
	SDL_Point point1( p1.x, p1.y );
	SDL_Point point2( p2.x, p2.y );
	SDL_RenderDrawLine( renderer, point1.x, point1.y, point2.x, point2.y );
}
