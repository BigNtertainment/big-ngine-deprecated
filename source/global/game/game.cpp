#include "game.h"

#define FPS 60


bool Game::running = true;
int Game::width = 640;
int Game::height = 480;

BigNgine::Scene* ActiveScene = nullptr;
SDL_Renderer* Game::renderer = nullptr;
SDL_Texture* Game::texture = nullptr;
SDL_Window* Game::window = nullptr;
SDL_Surface* Game::iconSurface = nullptr;
SDL_GLContext Game::context = nullptr;
std::string Game::Name = "BigNgine";
std::string Game::icon = "";

void Game::Stop() {
	SDL_Quit();
	Game::running = false;
}

void Game::Start(void(*Start)(), void(*Update)(int)) {
	
	// initialization of SDL libraries
	
	
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
		Logger::Error(SDL_GetError());
		return;
	}
	Mix_Init(MIX_INIT_MP3);
	

	
//	window
	Game::window = SDL_CreateWindow(Game::Name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Game::width, Game::height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

	
//	renderer
	Game::renderer = SDL_CreateRenderer(Game::window , -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
	if (!Game::renderer)
	{
		Logger::Error(SDL_GetError());
	}
	
	
//	starting every entity
	Start();
	ActiveScene->Start();

//	loading icon
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
	
	Game::context = SDL_GL_CreateContext(Game::window);
	glewInit();

	uint32_t lastTime = 0, currentTime;
	SDL_Event event;

//	main game loop
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
			
			
			glClearColor(0.0f, 1.0f, 0.0f, 0.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			SDL_GL_SwapWindow(Game::window);
			

			ActiveScene->Update(deltaTime);


			SDL_RenderPresent(Game::renderer);
			
			
			
			lastTime = SDL_GetTicks();

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
	SDL_GL_DeleteContext(Game::context);
	Game::iconSurface = nullptr;
	Game::window = nullptr;
	SDL_Quit();
}

void Game::SetActiveScene(BigNgine::Scene* scene) {
	ActiveScene = scene;
} 

void Game::ChangeActiveScene(BigNgine::Scene* scene) {
	ActiveScene->Destroy();

	ActiveScene = scene;

	ActiveScene->Start();
} 