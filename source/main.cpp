#include <iostream>
#include <SDL2/SDL.h>
#include <math.h>
#include "./project/namespaces/logger.h"

#define FPS 60
#define SPEED 6
#define WIDTH 640
#define HEIGHT 480

int main(int argc, char *args[])
{
	// //declaring shit
	// SDL_Window *window = nullptr;
	// SDL_Surface *windowSurface = nullptr;
	// SDL_Surface *imageSurface = nullptr;
	// SDL_Surface *playerSurface = nullptr;

	// //player pos init
	// SDL_Rect playerPos;
	// playerPos.w = 100;
	// playerPos.h = 100; 
	// playerPos.x = 0;
	// playerPos.y = 0;

	// //keyboard movment flags
	// bool keyW = false, keyA = false, keyS = false, keyD = false;

	// //initializing window
	// SDL_Init(SDL_INIT_VIDEO);

	// window = SDL_CreateWindow("BigNgine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);

	// //window created
	// bool isRunning = true;
	// SDL_Event ev;

	// //loading images
	// windowSurface = SDL_GetWindowSurface(window);
	// imageSurface = SDL_LoadBMP("assets/background_black.bmp");
	// playerSurface = SDL_LoadBMP("assets/mariss.bmp");

	// Uint32 colorkey = SDL_MapRGB(playerSurface->format, 0xFF, 0x00, 0xFF);
	// SDL_SetColorKey(playerSurface, SDL_TRUE, colorkey);

	// while (isRunning)
	// {

	// 	while (SDL_PollEvent(&ev) != 0)
	// 	{
	// 		if (ev.type == SDL_QUIT)
	// 			isRunning = false;
	// 		//keypress shit
	// 		else if (ev.type == SDL_KEYDOWN)
	// 		{
	// 			switch (ev.key.keysym.sym)
	// 			{
	// 			case SDLK_w:
	// 				keyW = true;
	// 				break;

	// 			case SDLK_s:
	// 				keyS = true;
	// 				break;

	// 			case SDLK_d:
	// 				keyD = true;
	// 				break;

	// 			case SDLK_a:
	// 				keyA = true;
	// 				break;
	// 			}
	// 		}
	// 		else if (ev.type == SDL_KEYUP)
	// 		{
	// 			switch (ev.key.keysym.sym)
	// 			{
	// 			case SDLK_w:
	// 				keyW = false;
	// 				break;

	// 			case SDLK_s:
	// 				keyS = false;
	// 				break;

	// 			case SDLK_d:
	// 				keyD = false;
	// 				break;

	// 			case SDLK_a:
	// 				keyA = false;
	// 				break;
	// 			}
	// 		}
	// 	}
	// 	//the main loop

	// 	//movment stuff
	// 	float x_vel = (keyD - keyA);
	// 	float y_vel = (keyS - keyW);

	// 	float magnitude = sqrt(pow(x_vel, 2) + pow(y_vel, 2));

	// 	if (magnitude != 0)
	// 	{
	// 		playerPos.x += floor((x_vel) / magnitude * SPEED);
	// 		playerPos.y += floor((y_vel) / magnitude * SPEED);
	// 	}

	// 	//collison stuff(with window border)
	// 	if (playerPos.x <= 0)
	// 		playerPos.x = 0;
	// 	if (playerPos.x >= WIDTH - playerPos.w)
	// 		playerPos.x = WIDTH - playerPos.w;
	// 	if (playerPos.y <= 0)
	// 		playerPos.y = 0;
	// 	if (playerPos.y >= HEIGHT - playerPos.h)
	// 		playerPos.y = HEIGHT - playerPos.h;

	// 	SDL_BlitSurface(imageSurface, NULL, windowSurface, NULL);
	// 	SDL_BlitSurface(playerSurface, NULL, windowSurface, &playerPos);

	// 	SDL_UpdateWindowSurface(window);
	// 	SDL_Delay(1000 / FPS);
	// }

	// //memory stuff
	// SDL_FreeSurface(imageSurface);
	// imageSurface = nullptr;
	// SDL_FreeSurface(playerSurface);
	// playerSurface = nullptr;
	// SDL_DestroyWindow(window);
	// window = nullptr;
	// windowSurface = nullptr;
	// SDL_Quit();

	Logger::Log("hello world!");

	return 0;
}