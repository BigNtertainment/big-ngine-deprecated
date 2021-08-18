#include "game.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_gpu.h>
#include "../input/input.h"
#include "../logger/logger.h"
#include "../../types/entity/entity.h"
#include "../../types/scene/scene.h"

#define FPS 60

bool Game::running = true;
int Game::width = 640;
int Game::height = 480;

BigNgine::Scene* ActiveScene = nullptr;
SDL_Renderer* Game::renderer = nullptr;
SDL_Texture* Game::texture = nullptr;
SDL_Window* Game::window = nullptr;
SDL_Surface* Game::iconSurface = nullptr;
std::string Game::Name = "BigNgine";
std::string Game::icon = "";

void Game::Stop() {
	SDL_Quit();
	Game::running = false;
}

void Game::Start(void(*Start)(), void(*Update)(int)) {

	// initialization of SDL libraries

	SDL_Init(SDL_INIT_VIDEO);
	SDL_Init(SDL_INIT_AUDIO);
	Mix_Init(MIX_INIT_MP3);

	
	//window and renderer
	Game::window = SDL_CreateWindow(Game::Name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Game::width, Game::height, SDL_WINDOW_SHOWN);
	Game::renderer = SDL_CreateRenderer(Game::window , -1, SDL_RENDERER_ACCELERATED);
	if (Game::renderer)
	{
		Logger::Error(SDL_GetError());
	}

	Start();

	ActiveScene->Start();

	iconSurface = SDL_LoadBMP(icon.c_str());
	if (!iconSurface)
	{
		Logger::Error("Couldn't load icon at: " + icon);
	}
	else
	{
		Uint32 colorKey = SDL_MapRGB(iconSurface->format, 0xFF, 0x00, 0xFF);
		SDL_SetColorKey(iconSurface, SDL_TRUE, colorKey);

		SDL_SetWindowIcon(Game::window, iconSurface);
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
			Uint64 start = SDL_GetPerformanceCounter();
			currentTime = SDL_GetTicks();

			SDL_RenderClear(Game::renderer);


			int deltaTime = currentTime - lastTime;

			Update(deltaTime);

			ActiveScene->Update(deltaTime);

			lastTime = SDL_GetTicks();


			SDL_RenderPresent(Game::renderer);

			Uint64 end = SDL_GetPerformanceCounter();

			float elapsedMS = (end - start) / (float)SDL_GetPerformanceFrequency() * 1000.0f;

			if (floor(16.666f - elapsedMS) > 0)
			{
				SDL_Delay(floor(16.666f - elapsedMS));
			}
		}
	}

	delete ActiveScene;

	SDL_DestroyWindow(Game::window);
	SDL_DestroyRenderer(Game::renderer);
	SDL_DestroyTexture(Game::texture);
	SDL_FreeSurface(Game::iconSurface);
	Game::iconSurface = nullptr;
	Game::window = nullptr;
	SDL_Quit();
//	GPU_Quit();
}

void Game::SetActiveScene(BigNgine::Scene* scene) {
	ActiveScene = scene;
} 

void Game::ChangeActiveScene(BigNgine::Scene* scene) {
	ActiveScene->Destroy();

	ActiveScene = scene;

	ActiveScene->Start();
} 