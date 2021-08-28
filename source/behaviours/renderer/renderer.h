#pragma once

#include "../../GLAD/glad.h"
#include <GLFW/glfw3.h>
#include "../../types/behaviour/behaviour.h"
#include <string>
#include <SDL2/SDL.h>
#include "../../global/game/game.h"
#include "../../global/logger/logger.h"
#include "../../global/fileSystem/fileSystem.h"

namespace BigNgine
{
	class RendererBehaviour : public Behaviour
	{
		friend class AnimationBehaviour;
	public:
		std::string file;
		std::string vertShader;
		std::string fragShader;

		void Start();

		void Update(int deltaTime);

		void Destroy();
	
	private:
		unsigned int VBO, VAO, EBO, program;
		SDL_Rect Position;
		SDL_Rect* AnimationRect = nullptr;

		SDL_Surface* Surface;
		SDL_Texture* Texture;
	};
}