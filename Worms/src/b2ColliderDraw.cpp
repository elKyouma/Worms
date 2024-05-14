#include "b2ColliderDraw.h"


void b2ColliderDraw::DrawPolygon( const b2Vec2* vertices, int32 vertexCount, const b2Color& color )
{
	SDL_Point* points = new SDL_Point[vertexCount];
	for ( int i = 0; i < vertexCount; i++ )
	{
		points[i].x = vertices[i].x;
		points[i].y = vertices[i].y;
	}
	SDL_RenderDrawLines( renderer, points, vertexCount );

	delete[] points;
}