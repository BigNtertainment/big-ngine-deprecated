#pragma once

#include "../../types/behaviour/behaviour.h"
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_gpu.h>
#include "../../global/game/game.h"
#include "../../global/logger/logger.h"

namespace BigNgine
{
	class RendererBehaviour : public Behaviour
	{
		friend class AnimationBehaviour;
	public:
		std::string file;

		void Start();

		void Update(int deltaTime);

		void Destroy();
	
	private:
		SDL_Rect Position;
		SDL_Rect* AnimationRect = nullptr;

		SDL_Surface* Surface;
	};
}