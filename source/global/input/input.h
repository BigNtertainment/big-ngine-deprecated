#include <SDL2/SDL.h>

namespace Input {
	bool Get(char key);

	void Update(SDL_Event event);
}