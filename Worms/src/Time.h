#pragma once
#include <SDL2/SDL.h>

namespace Time
{
	static double deltaTime = 0.0;

	class Timer
	{
	public:
		Timer()
		{
			lastTime = SDL_GetTicks64();
		}

		double Reset()
		{
			uint64_t newTime = SDL_GetTicks64();
			deltaTime = newTime - lastTime;
			lastTime = newTime;
			return deltaTime;
		}

		double Measure()
		{
			uint64_t newTime = SDL_GetTicks64();
			deltaTime = newTime - lastTime;
			return deltaTime;
		}

	private:
		uint64_t lastTime = 0;
		double deltaTime = 0.0;
	};
};