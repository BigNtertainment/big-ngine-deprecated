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
		
		
		///Set texture for sprite
		///@param path to png, bmp, whatever
		void SetDefaultTexture(std::string path);
		
		///Set vertex shader
		///@param vertexShader code in string
		void SetVertShader(std::string vertexShader);
		
		///Set fragment shader
		///@param fragmentShader code in string
		void SetFragShader(std::string fragmentShader);
	
	private:
		unsigned int VBO, VAO, EBO, program;
	};
}