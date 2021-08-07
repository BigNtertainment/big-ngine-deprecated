#pragma once
#include "../../types/behaviour/behaviour.h"
#include <string>
#include <SDL2/SDL.h>

namespace BigNgine
{
	class RendererBehaviour : public Behaviour
	{
	public:
		int width, height;

		std::string file;

		void Start();

		void Update(int deltaTime);

		void Destroy();
	
	private:
		SDL_Rect Position;

		SDL_Surface* Surface;
	};
}