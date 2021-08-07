#include <SDL2/SDL.h>

namespace Input {
	bool Get(long long key);

	void Update(SDL_Event event);
}