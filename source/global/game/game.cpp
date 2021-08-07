#include "game.h"
#include <SDL2/SDL.h>
#include "../input/input.h"
#include "../logger/logger.h"
#include "../../types/entity/entity.h"

#define WIDTH 640
#define HEIGHT 480
#define FPS 60

bool Game::running = true;

void Game::Stop() {
	SDL_Quit();
	Game::running = false;
}

void Game::Start(void(*Start)(), void(*Update)(int)) {
	// //declaring shit
	// SDL_Window *window = nullptr;
	// SDL_Surface *windowSurface = nullptr;
	// SDL_Surface *imageSurface = nullptr;
	// SDL_Surface *playerSurface = nullptr;

	// //initializing window
	// SDL_Init(SDL_INIT_VIDEO);

	// window = SDL_CreateWindow("fumo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	// //window created

	// //loading images
	// windowSurface = SDL_GetWindowSurface(window);

	Start();

	for(uint16_t i = 0; i < BigNgine::Entity::entities.size(); i++) {
		BigNgine::Entity::entities[i]->Start();
	}

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

			for(uint16_t i = 0; i < BigNgine::Entity::entities.size(); i++) {
				BigNgine::Entity::entities[i]->Update(currentTime - lastTime);
			}

			lastTime = SDL_GetTicks();

			SDL_Delay(1000 / FPS);
		}
	}

	for(uint16_t i = 0; i < BigNgine::Entity::entities.size(); i++) {
		delete BigNgine::Entity::entities[i];
	}

	// //memory stuff
	// SDL_FreeSurface(imageSurface);
	// imageSurface = nullptr;
	// SDL_FreeSurface(playerSurface);
	// playerSurface = nullptr;
	// SDL_DestroyWindow(window);
	// window = nullptr;
	// windowSurface = nullptr;
}