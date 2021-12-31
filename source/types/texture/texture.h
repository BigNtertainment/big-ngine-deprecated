#pragma once
#include "glad.h"
#include "GLFW/glfw3.h"
#include "stb_image.h"
#include "../../global/game/game.h"
#include "../../global/logger/logger.h"
#include "../../global/fileSystem/fileSystem.h"
#include <string>
#include <iostream>


namespace BigNgine{
	class Texture{
	public:
		Texture(const char* path);
		~Texture();

		void Bind(unsigned int slot = 0);
		void Unbind();

		[[nodiscard]] unsigned int getID() const;
		[[nodiscard]] int getWidth() const;
		[[nodiscard]] int getHeight() const;

	private:
		unsigned int _id;
		int _width, _height;
	};

};
