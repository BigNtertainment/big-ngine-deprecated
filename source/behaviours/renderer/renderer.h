#pragma once
#include "glad.h"
#include "GLFW/glfw3.h"
#include "stb_image.h"
#include "../../types/behaviour/behaviour.h"
#include "../../global/game/game.h"
#include "../../global/logger/logger.h"
#include "../../global/fileSystem/fileSystem.h"
#include <string>
#include <iostream>

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
	private:
		friend class AnimationBehaviour;
	public:
		std::string file;
		std::string vertShader = FileSystem::LoadFile("assets/shaders/vert/standard.glsl");
		std::string fragShader = FileSystem::LoadFile("assets/shaders/frag/textureStandard.glsl");
		
		void Start();
		
		void Update(int deltaTime);
		
		void Destroy();
		
		///Set vertex shader
		///@param vertexShader code in string
		///@default Default set to standard BigNgine vertex shader
		void SetVertShader(std::string vertexShader);
		
		///Set fragment shader
		///@param fragmentShader code in string
		///@default Default set to standard BigNgine fragment texture shader
		void SetFragShader(std::string fragmentShader);
		
		void setFile(const std::string &_file);
		
	
	private:
		unsigned int VBO, VAO, EBO, program, texture;
	};
}