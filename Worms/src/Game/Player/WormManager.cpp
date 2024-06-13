#include "Core/Input.h"
#include "Game/Player/WormManager.h"

SDL_Texture* createTexture( int team, SDL_Renderer* renderer ) {
	float width = 40.;
	float height = 10.;
	SDL_Surface* surface = SDL_CreateRGBSurface( 0, width, height, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000 );
	int r = 0;
	int g = 0;
	int b = 0;
	switch ( team ) {
	case 0:
		g = 255;
		break;
	case 1:
		r = 255;
		break;
	case 2:
		r = 255;
		g = 255;
		break;
	case 3:
		g = 255;
		b = 255;
		break;
	default:
		r = 255;
		g = 255;
		b = 255;
	}
	for ( int y = 0; y < height; y++ )
	{
		for ( int x = 0; x < width; x++ )
		{
			float prc = 0.4 + ((x / width) * 0.5);
			Uint32 color = SDL_MapRGB( surface->format, r * prc, g * prc, b * prc );
			Uint32* pixels = (Uint32*)surface->pixels;
			pixels[(y * surface->w) + x] = color;
		}
	}
	SDL_Texture* texture = SDL_CreateTextureFromSurface( renderer, surface );
	SDL_FreeSurface( surface );
	return texture;
};

WormManager::WormManager( SDL_Renderer* renderer, World* world, b2World* physicsWorld, Camera& camera, Weapon& weapon )
	: _renderer( renderer ), _world( world ), _teams(), physicsWorld( physicsWorld ), camera( camera ), weapon( weapon )
{
	camera.noTargetEvent = [&] ()
		{
			ChangeTeam();
			camera.ChangeTarget( _teams[_activeTeam]->getActiveWorm() );
			weapon.Activate();
		};
}

void WormManager::createTeam( int size )
{
	WormTeam* newTeam = new WormTeam;

	SDL_Texture* texture = createTexture( _teams.size(), _renderer );

	for ( int i = 0; i < size; i++ ) {
		newTeam->addWorm( new Worm( _renderer, _world, physicsWorld, camera, texture ) );
	}
	_teams.push_back( newTeam );
}

void WormManager::deleteTeam( WormTeam* team )
{
	_teams.erase( std::remove_if( _teams.begin(), _teams.end(),
				  [team] ( WormTeam* current ) {return team == current; } ) );
}

void WormManager::Update()
{
	if ( Input::Get().ChangeWorm() )
		ChangeActiveWorm();
	if ( Input::Get().ChangeTeam() )
		ChangeTeam();

	_teams[_activeTeam]->Update();
	if ( _teams[_activeTeam]->Size() == 0 ) {
		deleteTeam( _teams[_activeTeam] );
	}
	weapon.SetParent( GetActiveWormId() );
}

void WormManager::RenderHealthBars()
{
	for ( auto team : _teams )
	{
		team->RenderHealthBars();
	}
}

WormManager::~WormManager() {
	if ( !_teams.empty() )
	{
		for ( auto& team : _teams )
		{
			delete team;
			team = nullptr;
		}
		_teams.clear();
	}
}

void WormManager::ChangeTeam()
{
	if ( _teams.empty() ) return;

	_activeTeam += 1;
	if ( _activeTeam == _teams.size() )
		_activeTeam = 0;

	ChangeActiveWorm();
	camera.ChangeTarget( _teams[_activeTeam]->getActiveWorm() );
}

void WormManager::ChangeActiveWorm()
{
	if ( _teams.empty() ) return;
	_teams[_activeTeam]->changeActiveWorm();
}
