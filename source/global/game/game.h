#pragma once

#include "../../types/scene/scene.h"

namespace Game
{
	extern bool running;

	void Start(void(*Start)(), void(*Update)(int) );
	void Stop();

	extern BigNgine::Scene* ActiveScene;
};
