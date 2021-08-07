#pragma once
#include <string>
#include <SDL2/SDL.h>

#include "../../types/scene/scene.h"

namespace Game
{
	extern bool running;

	void Start(void(*Start)(), void(*Update)(int) );
	void Stop();

	extern BigNgine::Scene* ActiveScene;
	extern SDL_Window* window;
	extern SDL_Surface* windowSurface;
	extern std::string Name;
};
