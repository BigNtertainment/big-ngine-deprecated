#pragma once
#include "../../GLAD/glad.h"
#include <GLFW/glfw3.h>
#include "../../types/behaviour/behaviour.h"
#include <string>
#include "../../global/game/game.h"
#include "../../global/logger/logger.h"
#include "../../global/fileSystem/fileSystem.h"

namespace BigNgine
{
//	SHADER
//	====================================================================================================================
	class ShaderRendererBehaviour : public Behaviour
	{
		friend class AnimationBehaviour;
	public:
		std::string vertShader = FileSystem::LoadFile("assets/shaders/vert/standard.glsl");
		std::string fragShader;

		void Start();

		void Update(int deltaTime);

		void Destroy();
		
		///Set vertex shader
		///@param vertexShader code in string
		///@default Default set to standard BigNgine vertex shader
		void SetVertShader(std::string vertexShader);
		
		///Set fragment shader
		///@param fragmentShader code in string
		void SetFragShader(std::string fragmentShader);
	
	private:
		unsigned int VBO, VAO, EBO, program;
	};
	
//	TEXTURE
//	====================================================================================================================
	class TextureRendererBehaviour : public Behaviour
	{
		friend class AnimationBehaviour;
	public:
		std::string file;
		std::string vertShader = FileSystem::LoadFile("assets/shaders/vert/standard.glsl");
		std::string fragShader;
		
		void Start();
		
		void Update(int deltaTime);
		
		void Destroy();
		
		///Set vertex shader
		///@param vertexShader code in string
		///@default Default set to standard BigNgine vertex shader
		void SetVertShader(std::string vertexShader);
		
		///Set fragment shader
		///@param fragmentShader code in string
		void SetFragShader(std::string fragmentShader);
	
	private:
		unsigned int VBO, VAO, EBO, program;
	};
}