#pragma once

#include "glad.h"
#include "GLFW/glfw3.h"
#include "stb_image.h"
#include "../../types/behaviour/behaviour.h"
#include "../../global/game/game.h"
#include "../../global/logger/logger.h"
#include "../../types/texture/texture.h"
#include "../../types/vector2/vector2.h"
#include "../../types/vector3/vector3.h"
#include "../../global/fileSystem/fileSystem.h"
#include <string>
#include <iostream>
#include <map>
#include <vector>

#include <ft2build.h>
#include FT_FREETYPE_H

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
		
		void Update(int deltaTime) override;
		
		void Destroy() override;
		
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
		
		void Start() override;
		
		void Update(int deltaTime) override;
		
		void Destroy() override;
		
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
		void AddTexture(const char *_file);
		
		///Set texture
		void SetTexture(Texture *_texture);
	
	private:
		unsigned int VBO, VAO, EBO, program;
		Texture *texture;
	};


//	TEXT
//	====================================================================================================================
	struct Character
	{
		unsigned int TextureID;
		Vector2 Size;
		Vector2 Bearing;
		long Advance;
	};
	
	class TextRendererBehaviour : public Behaviour
	{
	
	public:
		std::string vertShader = FileSystem::LoadFile("assets/shaders/vert/text.glsl");
		std::string fragShader = FileSystem::LoadFile("assets/shaders/frag/textStandard.glsl");
		
		void Start() override;
		
		void Update(int deltaTime) override;
		
		void Destroy() override;
		
		///Set rendered text
		///@param _text  you want to render
		///@note Next line character should work fine. Change spacing between lines with SetMarginTop and SetMarginBottom
		///@default Default set to empty string
		void setText(const std::string &_text);
		
		///Set bottom margin of text line
		///@param marginBottom bottom margin of line in pixels
		///@dafault Default set to 0 pixels
		void setMarginBottom(short marginBottom);
		
		///Set top margin of text line
		///@param marginTop top margin of line in pixels
		///@dafault Default set to 0 pixels
		void setMarginTop(short marginTop);
		
		///Set font size in pixels
		///@param fontSize font size in pixels
		///@default 12 pixels
		void setFontSize(short fontSize);
		
		///Set font
		///@param font path to font from main.exe. IT MUST BE .ttf FILE
		///@note All font files should be in /assets/fonts/
		///@default Default set to Jetbrains Mono font in /assets/fonts/ folder
		void setFont(const std::string &font);

		void setColor(Vector3 color);
	
	private:
		FT_Library ft;
		FT_Face face;
		unsigned int VBO, VAO, EBO, program;
		short int font_size = 12, margin_top = 0, margin_bottom = 0;
		std::map<char, BigNgine::Character> Characters = std::map<char, BigNgine::Character>();
		std::string text, font = "assets/fonts/JetBrainsMono-Medium.ttf";
		Vector3 text_color = Vector3(255.f, 255.f, 255.f);
		std::string::const_iterator c;
	};
}