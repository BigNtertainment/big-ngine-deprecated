#include "input.h"

static bool* initKeys() {
	bool* keys = new bool[256];

	for(uint16_t i = 0; i < 256; i++)
		keys[i] = false;
	
	return keys;
}

static bool* keys = initKeys();

bool Input::Get(char key) {
	return keys[(int)key];
}

void Input::Update(SDL_Event event) {
	if (event.type == SDL_KEYDOWN)
	{
		keys[event.key.keysym.sym] = true;
	}
	else if (event.type == SDL_KEYUP)
	{
		keys[event.key.keysym.sym] = false;
	}
}