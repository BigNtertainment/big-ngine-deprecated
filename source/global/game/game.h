#pragma once

namespace Game
{
	extern bool running;

	void Start(void(*Start)(), void(*Update)(int) );
	void Stop();
};
