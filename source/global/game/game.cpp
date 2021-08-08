#include "game.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "../input/input.h"
#include "../logger/logger.h"
#include "../../types/entity/entity.h"
#include "../../types/scene/scene.h"

#define FPS 60

bool Game::running = true;
int Game::width = 640;
int Game::height = 480;

BigNgine::Scene* Game::ActiveScene = nullptr;
SDL_Window* Game::window = nullptr;
SDL_Surface* Game::windowSurface = nullptr;
std::string Game::Name;

void Game::Stop() {
	SDL_Quit();
	Game::running = false;
}

void Game::Start(void(*Start)(), void(*Update)(int)) {

	// that is init init?

	SDL_Init(SDL_INIT_VIDEO);
	SDL_Init(SDL_INIT_AUDIO);
	Mix_Init(MIX_INIT_MP3);

	
	//window shit
	Game::window = SDL_CreateWindow(Game::Name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Game::width, Game::height, SDL_WINDOW_SHOWN);
	Game::windowSurface = SDL_GetWindowSurface(Game::window);

	Start();

	Game::ActiveScene->Start();

	uint32_t lastTime = 0, currentTime;
	SDL_Event event;

	while(Game::running) {
		while (SDL_PollEvent(&event) != 0)
		{
			if (event.type == SDL_QUIT) {
				Game::Stop();
			}
			
			Input::Update(event);
		}

		if(Game::running) {
			currentTime = SDL_GetTicks();

			Update(currentTime - lastTime);

			Game::ActiveScene->Update(currentTime - lastTime);

			lastTime = SDL_GetTicks();

			// bliting player to background @ playerPos
			SDL_UpdateWindowSurface(Game::window);

			SDL_Delay(1000 / FPS);
		}
	}

	delete Game::ActiveScene;

	SDL_DestroyWindow(Game::window);
	Game::window = nullptr;
	Game::windowSurface = nullptr;
}