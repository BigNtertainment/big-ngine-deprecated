#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <math.h>
#include "global/logger/logger.h"
#include "global/game/game.h"
#include "global/input/input.h"
#include "global/fileSystem/fileSystem.h"
#include "types/entity/entity.h"
#include "types/scene/scene.h"
#include "types/behaviour/behaviour.h"

#define FPS 60
#define SPEED 400
#define WIDTH 640
#define HEIGHT 480

SDL_Window *window = nullptr;
SDL_Surface *windowSurface = nullptr;
SDL_Surface *imageSurface = nullptr;
SDL_Surface *playerSurface = nullptr;

SDL_Rect playerPos;

BigNgine::Scene* firstScene;
BigNgine::Scene* secondScene;
BigNgine::Entity* man;
BigNgine::Behaviour* funny;

class FunnyBehaviour : public BigNgine::Behaviour {
public:
	FunnyBehaviour() {
		name = "funny";
	}

	float funnyNumber;

	void Start() {
		Logger::Log("Start");
		funnyNumber = 0;
	}

	void Update(int deltaTime) {
		funnyNumber += (float)deltaTime / 1000;

		Logger::Log(funnyNumber);

		if(funnyNumber >= 5.0) {
			Game::ActiveScene = secondScene;
		}
	}

	void Destroy() {
		Logger::Log("Goodbye!");
	}
};

void Start() {
	//initializing window
	SDL_Init(SDL_INIT_VIDEO);

	//player pos init
	playerPos.w = 100;
	playerPos.h = 100; 
	playerPos.x = 0;
	playerPos.y = 0;

	//initializing window
	SDL_Init(SDL_INIT_VIDEO);

	if (SDL_Init(SDL_INIT_AUDIO) < 0)
		Logger::Error("cant load SDL_AUDIO");

	Mix_Init(MIX_INIT_MP3);

	Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 );
	window = SDL_CreateWindow("fumo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	//window created

	//loading images
	windowSurface = SDL_GetWindowSurface(window);

	//loading images
	windowSurface = SDL_GetWindowSurface(window);
	imageSurface = SDL_LoadBMP("assets/background_black.bmp");
	playerSurface = SDL_LoadBMP("assets/mariss.bmp");

	
	Uint32 colorkey = SDL_MapRGB(playerSurface->format, 0xFF, 0x00, 0xFF);
	SDL_SetColorKey(playerSurface, SDL_TRUE, colorkey);

	firstScene = new BigNgine::Scene();
	secondScene = new BigNgine::Scene();

	man = new BigNgine::Entity();

	funny = new FunnyBehaviour();

	man->AddBehaviour(funny);

	firstScene->AddEntity(man);

	Game::ActiveScene = firstScene;
}

void Update(int deltaTime) {
	//making player with Rect to later blit him into window
	// TODO this is stupid and overcomplicated but i dont know how to do it better

	//movment stuff
	float x_vel = (Input::Get(SDLK_d) - Input::Get(SDLK_a));
	float y_vel = (Input::Get(SDLK_s) - Input::Get(SDLK_w));

	float magnitude = sqrt(pow(x_vel, 2) + pow(y_vel, 2));

	if (magnitude != 0)
	{
		playerPos.x += (x_vel / magnitude * SPEED * deltaTime / 1000);
		playerPos.y += (y_vel / magnitude * SPEED * deltaTime / 1000);
	}

	//collison stuff(with window border)
	if (playerPos.x <= 0)
		playerPos.x = 0;
	if (playerPos.x >= WIDTH - playerPos.w)
		playerPos.x = WIDTH - playerPos.w;
	if (playerPos.y <= 0)
		playerPos.y = 0;
	if (playerPos.y >= HEIGHT - playerPos.h)
		playerPos.y = HEIGHT - playerPos.h;

	// bliting background to window surface 
	SDL_BlitSurface(imageSurface, NULL, windowSurface, NULL);
	// bliting player to background @ playerPos
	SDL_BlitSurface(playerSurface, NULL, windowSurface, &playerPos);

	SDL_UpdateWindowSurface(window);
}

int main(int argc, char *args[])
{
	try {
		Game::Start(Start, Update);
	} catch (std::exception e) {
		Logger::Error(e.what());
	}

	//memory stuff
	SDL_FreeSurface(imageSurface);
	imageSurface = nullptr;
	SDL_FreeSurface(playerSurface);
	playerSurface = nullptr;
	SDL_DestroyWindow(window);
	window = nullptr;
	windowSurface = nullptr;
	SDL_Quit();
	Mix_Quit();

	return 0;
}