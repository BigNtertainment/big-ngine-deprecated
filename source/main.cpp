#include <iostream>
#include <SDL2/SDL.h>
#include <math.h>
#include "global/game/game.h"
#include "global/input/input.h"

#define FPS 60
#define SPEED 6
#define WIDTH 640
#define HEIGHT 480

int main(int argc, char *args[])
{
	//declaring shit
	SDL_Window *window = nullptr;
	SDL_Surface *windowSurface = nullptr;
	SDL_Surface *imageSurface = nullptr;
	SDL_Surface *playerSurface = nullptr;

	//player pos init
	SDL_Rect playerPos;
	playerPos.w = 100;
	playerPos.h = 100; 
	playerPos.x = 0;
	playerPos.y = 0;

	//initializing window
	SDL_Init(SDL_INIT_VIDEO);

	window = SDL_CreateWindow("fumo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);

	//window created
	SDL_Event event;

	//loading images
	windowSurface = SDL_GetWindowSurface(window);
	imageSurface = SDL_LoadBMP("assets/background.bmp");
	playerSurface = SDL_LoadBMP("assets/mariss.bmp");

	Uint32 colorkey = SDL_MapRGB(playerSurface->format, 0xFF, 0x00, 0xFF);
	SDL_SetColorKey(playerSurface, SDL_TRUE, colorkey);

	//making player with Rect to later blit him into window
	// TODO this is stupid and overcomplicated but i dont know how to do it better
	while (Game::running)
	{
		while (SDL_PollEvent(&event) != 0)
		{
			if (event.type == SDL_QUIT)
				Game::Stop();
			
			Input::Update(event);
		}
		//the main loop

		//movment stuff
		float x_vel = (Input::Get(SDLK_d) - Input::Get(SDLK_a));
		float y_vel = (Input::Get(SDLK_s) - Input::Get(SDLK_w));

		float magnitude = sqrt(pow(x_vel, 2) + pow(y_vel, 2));

		if (magnitude != 0)
		{
			playerPos.x += floor((x_vel) / magnitude * SPEED);
			playerPos.y += floor((y_vel) / magnitude * SPEED);
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

		SDL_BlitSurface(imageSurface, NULL, windowSurface, NULL);
		SDL_BlitSurface(playerSurface, NULL, windowSurface, &playerPos);

		SDL_UpdateWindowSurface(window);
		SDL_Delay(1000 / FPS);
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

	return 0;
}