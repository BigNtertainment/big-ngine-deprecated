#pragma once

#include "../input/input.h"
#include "../logger/logger.h"
#include "../../types/entity/entity.h"
#include "../../types/scene/scene.h"
#include "../../types/scene/scene.h"
#include "glad.h"
#include "GLFW/glfw3.h"
#include "stb_image.h"
#include <chrono>
#include <thread>
#include <string>
#include <ctime>

namespace Game
{
	extern bool running;
	extern int width;
	extern int height;
	extern const char *icon;
	
///	Function that starts game, should be called once at the start your program.
///	@param Start Function that is called once.
/// @param Update Function that is called every frame.
	void Start(void(*Start)(), void(*Update)(int));
///	Stops game
	void Stop();
	
///	Sets active scene.
///	@param scene BigNgine::Scene* scene
/// @warning Should only be called once. When other scene is running you should use ChangeActiveScene().
	void SetActiveScene(BigNgine::Scene* scene);
///	Changes active scene, calls deconstructor of current running scene and then calls start sequence of new scene.
///	@param scene BigNgine::Scene* scene
	void ChangeActiveScene(BigNgine::Scene* scene);

	extern GLFWwindow* window;
	extern const char *name;
};
