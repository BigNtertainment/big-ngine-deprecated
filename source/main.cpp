#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include <math.h>
#include <Box2D/Box2D.h>
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

SDL_Surface *iconSurface = nullptr;

class MovementBehaviour : public BigNgine::Behaviour {
	void Start() {}

	void Update(int deltaTime) {
		//movment stuff
		float x_vel = (Input::Get((int)SDLK_d) - Input::Get((int)SDLK_a));
		float y_vel = (Input::Get((int)SDLK_s) - Input::Get((int)SDLK_w));

		float magnitude = sqrt(pow(x_vel, 2) + pow(y_vel, 2));

		if (magnitude != 0)
		{
			parent->position.x += (x_vel / magnitude * SPEED * deltaTime / 1000);
			parent->position.y += (y_vel / magnitude * SPEED * deltaTime / 1000);
		}

		//collison stuff(with window border)
		if (parent->position.x <= 0)
			parent->position.x = 0;
		if (parent->position.x >= Game::width - 100)
			parent->position.x = Game::width - 100;
		if (parent->position.y <= 0)
			parent->position.y = 0;
		if (parent->position.y >= Game::height - 100)
			parent->position.y = Game::height - 100;
	}

	void Destroy() {

	}
};

BigNgine::Scene* Scene;

BigNgine::Entity* Player;

void Start()
{
	Player = new BigNgine::Entity();
	Player->size = BigNgine::Vector2(100.0, 100.0);
	
	BigNgine::RendererBehaviour* PlayerRenderer = new BigNgine::RendererBehaviour();
	BigNgine::RendererBehaviour* BackgroundRenderer = new BigNgine::RendererBehaviour();

	MovementBehaviour* PlayerMovement = new MovementBehaviour();

	Scene = new BigNgine::Scene();

	PlayerRenderer->file = "assets/mariss.bmp";

	BackgroundRenderer->file = "assets/background.bmp";

	Scene->Camera->AddBehaviour(BackgroundRenderer);
	Player->AddBehaviour(PlayerRenderer);
	Player->AddBehaviour(PlayerMovement);

	Scene->AddEntity(Player);

	Game::icon = "assets/icon.bmp";
	Game::ActiveScene = Scene;

}

void Update(int deltaTime)
{

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

	return 0;
}