#pragma once
#include "Core/Initialization/App.h"
class Game : public App
{
public:
	void InitWindow( const std::string& title, const int width, const int height ) final;
	void Update() final;
	//void HandleEvents() final;
	void Render() final;

private:
	void setUpDebugDraw( std::unique_ptr<Camera, std::default_delete<Camera>>& camera );

	std::unique_ptr<WormManager> wormManager;
	Weapon* weapon;
};

