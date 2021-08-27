#pragma once


#include "../../GLAD/glad.h"
#include <GLFW/glfw3.h>

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include "../input/input.h"
#include "../logger/logger.h"
#include "../../types/entity/entity.h"
#include "../../types/scene/scene.h"
#include "../../types/scene/scene.h"
#include "../../STBI/stb_image.h"

namespace Game
{
	extern bool running;
	extern int width;
	extern int height;
	extern const char *icon;

	void Start(void(*Start)(), void(*Update)(int) );
	void Stop();

	void SetActiveScene(BigNgine::Scene* scene);
	void ChangeActiveScene(BigNgine::Scene* scene);

	extern SDL_Renderer* renderer;
	extern SDL_Texture* texture;
	extern GLFWwindow* window;
	extern const char *Name;
};
