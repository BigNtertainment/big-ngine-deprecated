#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include "renderer.h"
#include "../../global/game/game.h"
#include "../../global/logger/logger.h"

void BigNgine::RendererBehaviour::Start()
{
	Surface = SDL_LoadBMP( BigNgine::RendererBehaviour::file.c_str() );
	// TODO: error detection
	if (!Surface)
	{
		Logger::Error("Couldn`t load file: " + file);
		return;
	}
	
	Uint32 colorkey = SDL_MapRGB(Surface->format, 0xFF, 0x00, 0xFF);
	SDL_SetColorKey(Surface, SDL_TRUE, colorkey);
	Position.w = 1;
	Position.h = 1;
	Position.x = 0;
	Position.y = 0;
}

void BigNgine::RendererBehaviour::Update(int deltaTime)
{
	Position.x = (int)parent->position.x - (int)parent->GetParentScene()->Camera->position.x;
	Position.y = (int)parent->position.y - (int)parent->GetParentScene()->Camera->position.y;
	Position.w = (int)parent->size.x;
	Position.h = (int)parent->size.y;

	SDL_BlitSurface(Surface, (AnimationRect == nullptr ? NULL : AnimationRect), Game::windowSurface, &Position);
}

void BigNgine::RendererBehaviour::Destroy()
{
	SDL_FreeSurface(Surface);
	Surface = nullptr;
}
