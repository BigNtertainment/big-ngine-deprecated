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
#include <time.h>

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

	extern GLFWwindow* window;
	extern const char *name;
};
