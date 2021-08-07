#include "input.h"

static bool* initKeys() {
	bool* keys = new bool[256];

	for(uint16_t i = 0; i < 256; i++)
		keys[i] = false;
	
	return keys;
}

static bool* keys = initKeys();

bool Input::Get(long long key) {
	if(key > 127)
	{
		key -= 0x40000000 + 127;
	}

	return keys[(int)key];
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
}