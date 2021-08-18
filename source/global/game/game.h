#pragma once

#include <string>
#include <SDL2/SDL.h>

#include "../../types/scene/scene.h"

namespace Game
{
	extern bool running;
	extern int width;
	extern int height;
	extern std::string icon;

	void Start(void(*Start)(), void(*Update)(int) );
	void Stop();

	void SetActiveScene(BigNgine::Scene* scene);
	void ChangeActiveScene(BigNgine::Scene* scene);

	extern SDL_Renderer* renderer;
	extern SDL_Texture* texture;
	extern SDL_Window* window;
	extern SDL_Surface* windowSurface;
	extern SDL_Surface* iconSurface;
	extern std::string Name;
};
