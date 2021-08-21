#pragma once

#include <string>
#include <GL/glew.h>
#include <Gl/gl.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_opengl_glext.h>
#include <SDL2/SDL_mixer.h>
#include "../input/input.h"
#include "../logger/logger.h"
#include "../../types/entity/entity.h"
#include "../../types/scene/scene.h"
#include "../../types/scene/scene.h"

namespace Game
{
	extern bool running;
	extern int width;
	extern int height;
	extern std::string icon;

	void Start(void(*Start)(), void(*Update)(int) );
	void Stop();

	void SetActiveScene(BigNgine::Scene* scene);
	void ChangeActiveScene(BigNgine::Scene* scene);

	extern SDL_Renderer* renderer;
	extern SDL_Texture* texture;
	extern SDL_Window* window;
	extern SDL_Surface* iconSurface;
	extern SDL_GLContext context;
	extern std::string Name;
};
