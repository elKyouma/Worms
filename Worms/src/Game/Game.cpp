#include <imgui_impl_sdlrenderer2.h>
#include <SDL2/SDL.h>
#include "Core/Input.h"
#include "Core/Physics/ColliderFactory.h"
#include "Core/Physics/ContactManager.h"
#include "Core/Time.h"
#include "Game.h"
#include "imgui_impl_sdl2.h"
#include "Terminal/Terminal.h"

void Game::InitWindow( const std::string& title, const int width, const int height )
{
	App::InitWindow( title, width, height );

	world = std::make_unique<World>( renderer );
	world->RegisterComponent<Position>();
	world->RegisterComponent<Rotation>();
	world->RegisterComponent<Health>();
	world->RegisterComponent<Sprite>();
	world->RegisterComponent<Motion>();
	world->RegisterComponent<RigidBody>();
	world->RegisterComponent<Follow>();
	world->RegisterSystem<Movement>();
	world->RegisterSystem<PhysicsSynchronizer>();
	world->RegisterSystem<TargetSystem>();
	camera = std::make_unique<Camera>( renderer, world.get() );
	world->RegisterSystem<SpriteRenderer>( renderer, *camera );

	physicsWorld = std::make_unique<b2World>( b2Vec2( 0, -9.811f ) );
	b2DebugDraw = std::make_unique<b2ColliderDraw>( renderer, *camera );
	physicsWorld->SetDebugDraw( b2DebugDraw.get() );
	physicsWorld->SetContactListener( &ContactManager::Get() );
	ColliderFactory::Get().Init( physicsWorld.get() );

	wormManager = std::make_unique<WormManager>( renderer, world.get(), physicsWorld.get(), camera.get() );
	wormManager->createTeam( 4 );
	wormManager->createTeam( 4 );
	GameObject::activeObjs.emplace_back( std::make_unique<Map>( physicsWorld.get() ) );
	auto weapon = std::make_unique<Weapon>( *camera );
	this->weapon = weapon.get();
	GameObject::activeObjs.emplace_back( std::move( weapon ) );

	for ( auto& gameObject : GameObject::activeObjs )
		gameObject->Initialise( renderer, world.get() );

}

void Game::Update()
{
	App::Update();

	world->Update();
	physicsWorld->Step( static_cast<float>(Time::deltaTime), 8, 3 );
	wormManager->Update();
	weapon->SetParent( wormManager->GetActiveWormId() );
	camera->Update();

	for ( auto& gameObject : GameObject::activeObjs )
		gameObject->Update();
}

void Game::Render()
{
	for ( auto& gameObject : GameObject::activeObjs )
		gameObject->Render();

	world->Render();
	//weapon->Render();
}
