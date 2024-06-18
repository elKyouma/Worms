#include "Core/Input.h"
#include "Game/Player/WormManager.h"

SDL_Texture* createTexture( int team, SDL_Renderer* renderer ) {
	float width = 40.;
	float height = 10.;
	SDL_Surface* surface = SDL_CreateRGBSurface( 0, width, height, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000 );
	if ( !surface ) {
		return nullptr;
	}

	Uint8 colors[4][3] = {
		{0, 255, 0},  // team 0: green
		{255, 0, 0},  // team 1: red
		{255, 255, 0},// team 2: yellow
		{0, 255, 255} // team 3: cyan
	};

	Uint8 r = 255, g = 255, b = 255; // default: white
	if ( team < 4 ) {
		r = colors[team][0];
		g = colors[team][1];
		b = colors[team][2];
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
			if ( _teams.size() != 0 ) {
				camera.ChangeTarget( _teams[_activeTeam]->getActiveWorm() );
				weapon.Activate();
			}
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

void WormManager::ChangeTeam()
{
	if ( _teams.empty() ) return;

	_activeTeam = (_activeTeam + 1) % _teams.size();
	ChangeActiveWorm();
	camera.ChangeTarget( _teams[_activeTeam]->getActiveWorm() );
}

void WormManager::ChangeActiveWorm()
{
	if ( !_teams.empty() )
		_teams[_activeTeam]->changeActiveWorm();
}

void WormManager::Update()
{
	if ( Input::Get().ChangeWorm() ) ChangeActiveWorm();
	if ( Input::Get().ChangeTeam() ) ChangeTeam();
	if ( _teams.empty() ) return;

	_teams[_activeTeam]->Update();

	if ( _teams[_activeTeam]->Size() == 0 ) {
		deleteTeam( _teams[_activeTeam] );
	}
	if ( !_teams.empty() )
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