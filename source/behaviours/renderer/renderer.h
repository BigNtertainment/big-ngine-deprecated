#pragma once
#include "glad.h"
#include "GLFW/glfw3.h"
#include "stb_image.h"
#include "../../types/behaviour/behaviour.h"
#include "../../global/game/game.h"
#include "../../global/logger/logger.h"
#include "../../types/texture/texture.h"
#include "../../global/fileSystem/fileSystem.h"
#include <string>
#include <iostream>
#include <vector>

namespace BigNgine
{
//	SHADER
//	====================================================================================================================
	class ShaderRendererBehaviour : public Behaviour
	{
	public:
		std::string vertShader = FileSystem::LoadFile("assets/shaders/vert/standard.glsl");
		std::string fragShader;

		void Start() override;

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
		std::vector<const char *> texturePaths;
		std::string vertShader = FileSystem::LoadFile("assets/shaders/vert/standard.glsl");
		std::string fragShader = FileSystem::LoadFile("assets/shaders/frag/textureStandard.glsl");
		bool yFlipped, xFlipped;
		
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
		
///		Set texture
///		@param _file Path to your file of choice(should be picture)
		void AddTexture(const char * _file);
		
		///Set texture
		void SetTexture(Texture * _texture);
  
		
	
	private:
		unsigned int VBO, VAO, EBO, program;
		Texture* texture;
	};
}