#include "input.h"
//#include "../../types/vector2/vector2.h"

static bool* initKeys() {
	bool* keys = new bool[256];

	for(uint16_t i = 0; i < 256; i++)
		keys[i] = false;
	
	return keys;
}

static bool* keys = initKeys();
Input::MouseStruct Mouse;

bool Input::Get(long long key) {
	if(key > 127)
	{
		key -= 0x40000000 + 127;
	}

	return keys[(int)key];
}

Input::MouseStruct Input::GetMouse()
{
	return Mouse;
}

void Input::Update(SDL_Event event) {
	int key;
	if (event.key.keysym.sym > 127)
	{
		key = event.key.keysym.sym - 0x40000000 + 127;
	}
	else
	{
		key = event.key.keysym.sym;
	}

	if (event.type == SDL_KEYDOWN)
	{
		keys[key] = true;
	}
	else if (event.type == SDL_KEYUP)
	{
		keys[key] = false;
	}
	else if (event.type == SDL_MOUSEMOTION)
	{
		Mouse.MousePosition.x = event.button.x;
		Mouse.MousePosition.y = event.button.y;
	}
	else if (event.type == SDL_MOUSEBUTTONDOWN)
	{
		switch (event.button.button)
		{
			case SDL_BUTTON_LEFT:
			{
				Mouse.LeftButton = true;
				break;
			}
			
			case SDL_BUTTON_RIGHT:
			{
				Mouse.RightButton = true;
				break;
			}
			
			case SDL_BUTTON_MIDDLE:
			{
				Mouse.MiddleButton = true;
				break;
			}
			
			case SDL_BUTTON_X1:
			{
				Mouse.SideButton2 = true;
				break;
			}
			
			case SDL_BUTTON_X2:
			{
				Mouse.SideButton1 = true;
				break;
			}
		}
	}
	else if (event.type == SDL_MOUSEBUTTONUP)
	{
		switch (event.button.button)
		{
			case SDL_BUTTON_LEFT:
			{
				Mouse.LeftButton = false;
				break;
			}
			
			case SDL_BUTTON_RIGHT:
			{
				Mouse.RightButton = false;
				break;
			}
			
			case SDL_BUTTON_MIDDLE:
			{
				Mouse.MiddleButton = false;
				break;
			}
			
			case SDL_BUTTON_X1:
			{
				Mouse.SideButton2 = false;
				break;
			}
			
			case SDL_BUTTON_X2:
			{
				Mouse.SideButton1 = false;
				break;
			}
		}
	}
}