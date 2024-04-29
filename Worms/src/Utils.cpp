#include "Utils.h"

SDL_Texture* IMG_LoadTexture( SDL_Renderer* renderer, const char* file )
{
	SDL_Texture* texture = NULL;
	SDL_Surface* surface = IMG_Load( file );
	if ( surface ) {
		texture = SDL_CreateTextureFromSurface( renderer, surface );
		SDL_FreeSurface( surface );
	}

	return texture;
}