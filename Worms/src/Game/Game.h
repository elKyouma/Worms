#pragma once
#include "Core/Initialization/App.h"

class Game : public App
{
public:
	void InitWindow( const std::string& title, const int width, const int height ) final;
	void Update() final;
	//void HandleEvents() final;
	void Render() final;
	//void Clean() final;

private:

	std::unique_ptr<Map> map;
	std::unique_ptr<WormManager> wormManager;
	std::unique_ptr<Weapon> weapon;
};

