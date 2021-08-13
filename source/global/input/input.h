#pragma once
#include <SDL2/SDL.h>
#include "../../types/vector2/vector2.h"

namespace Input {
	bool Get(long long key);

	void Update(SDL_Event event);
	
	
	struct MouseStruct
	{
		bool RightButton = false;
		bool LeftButton = false;
		bool MiddleButton = false;
		bool SideButton1 = false;
		bool SideButton2 = false;
		BigNgine::Vector2 MousePosition = BigNgine::Vector2(0.0f, 0.0f);
	};
	
	MouseStruct GetMouse();
}