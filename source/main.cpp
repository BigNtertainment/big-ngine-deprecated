#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include <math.h>
#include "global/logger/logger.h"
#include "global/game/game.h"
#include "global/input/input.h"
#include "global/fileSystem/fileSystem.h"
#include "types/entity/entity.h"
#include "types/scene/scene.h"
#include "types/behaviour/behaviour.h"
#include "behaviours/renderer/renderer.h"

#define FPS 60
#define SPEED 400
#define WIDTH 640
#define HEIGHT 480



SDL_Surface *imageSurface = nullptr;
SDL_Surface *iconSurface = nullptr;

BigNgine::Scene* firstScene;
BigNgine::Scene* secondScene;
BigNgine::Entity* man;
BigNgine::Behaviour* funny;

BigNgine::Entity* Player;


void Start()
{
	Player = new BigNgine::Entity();
	BigNgine::RendererBehaviour* PlayerRenderer = new BigNgine::RendererBehaviour();
	PlayerRenderer->width = 100;
	PlayerRenderer->height = 100;
	PlayerRenderer->file = "assets/marisss.bmp";
	Player->addBehaviour(PlayerRenderer);



	
	//loading images
	imageSurface = SDL_LoadBMP("assets/background_black.bmp");
	iconSurface = SDL_LoadBMP("assets/icon.bmp");

	Uint32 colorkey = SDL_MapRGB(iconSurface->format, 0xFF, 0x00, 0xFF);
	SDL_SetColorKey(iconSurface, SDL_TRUE, colorkey);

	firstScene = new BigNgine::Scene();
	secondScene = new BigNgine::Scene();

	man = new BigNgine::Entity();

	funny = new FunnyBehaviour();

	man->AddBehaviour(funny);

	firstScene->AddEntity(man);

	Game::ActiveScene = firstScene;
	SDL_SetWindowIcon(Game::window, iconSurface);

}

void Update(int deltaTime)
{

	//movment stuff
	float x_vel = (Input::Get((int)SDLK_d) - Input::Get((int)SDLK_a));
	float y_vel = (Input::Get((int)SDLK_s) - Input::Get((int)SDLK_w));

	float magnitude = sqrt(pow(x_vel, 2) + pow(y_vel, 2));

	if (magnitude != 0)
	{
		Player->position.x += (x_vel / magnitude * SPEED * deltaTime / 1000);
		Player->position.y += (y_vel / magnitude * SPEED * deltaTime / 1000);
	}

	//collison stuff(with window border)
	if (Player->position.x <= 0)
		Player->position.x = 0;
	if (Player->position.x >= WIDTH - 100)
		Player->position.x = WIDTH - 100;
	if (Player->position.y <= 0)
		Player->position.y = 0;
	if (Player->position.y >= HEIGHT - 100)
		Player->position.y = HEIGHT - 100;

	// bliting background to window surface
	SDL_BlitSurface(imageSurface, NULL, Game::windowSurface, NULL);
	// bliting player to background @ playerPos
	SDL_UpdateWindowSurface(Game::window);
}

int main(int argc, char *args[])
{
	Game::Name = "BigNgine";
	try
	{
		Game::Start(Start, Update);
	}
	catch (std::exception e)
	{
		Logger::Error(e.what());
	}

	//memory stuff
	SDL_FreeSurface(imageSurface);
	imageSurface = nullptr;
	return 0;
}