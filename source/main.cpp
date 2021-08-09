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
#include "behaviours/physicsStatic/physicsStatic.h"
#include "behaviours/physics/physics.h"
#include "behaviours/animation/animation.h"

#define FPS 80
#define SPEED 200

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
			// parent->position.y += (y_vel / magnitude * SPEED * deltaTime / 1000);
		}

		// //collison stuff(with window border)
		// if (parent->position.x <= 0)
		// 	parent->position.x = 0;
		// if (parent->position.x >= Game::width - 100)
		// 	parent->position.x = Game::width - 100;
		// if (parent->position.y <= 0)
		// 	parent->position.y = 0;
		// if (parent->position.y >= Game::height - 100)
		// 	parent->position.y = Game::height - 100;
	}

	void Destroy() {

	}
};

BigNgine::Scene* Scene;

BigNgine::Entity* Player;
BigNgine::Entity* AnimatedEntity;

BigNgine::Entity* Floor;

void Start()
{
	Player = new BigNgine::Entity();
	AnimatedEntity = new BigNgine::Entity();

	Player->SetDefaultSize(BigNgine::Vector2(100.0, 100.0));
	Player->SetDefaultPosition(BigNgine::Vector2(50.0, 50.0));
	AnimatedEntity->SetDefaultPosition(BigNgine::Vector2(Game::width / 2, Game::height / 2));
	AnimatedEntity->SetDefaultSize(BigNgine::Vector2(100.0, 100.0));
	
	BigNgine::RendererBehaviour* PlayerRenderer = new BigNgine::RendererBehaviour();
	BigNgine::RendererBehaviour* AnimatedEntityRenderer = new BigNgine::RendererBehaviour();
	BigNgine::RendererBehaviour* BackgroundRenderer = new BigNgine::RendererBehaviour();

	BigNgine::AnimationBehaviour* Animation = new BigNgine::AnimationBehaviour();

	MovementBehaviour* PlayerMovement = new MovementBehaviour();
	BigNgine::PhysicsBehaviour* PlayerPhysics = new BigNgine::PhysicsBehaviour();

	Floor = new BigNgine::Entity();

	Floor->SetDefaultSize(BigNgine::Vector2(640.0, 40.0));
	Floor->SetDefaultPosition(BigNgine::Vector2(0.0, 440.0));

	BigNgine::RendererBehaviour* FloorRenderer = new BigNgine::RendererBehaviour();
	BigNgine::PhysicsStaticBehaviour* FloorPhysics = new BigNgine::PhysicsStaticBehaviour();

	Scene = new BigNgine::Scene();

	BackgroundRenderer->file = "assets/background.bmp";
	PlayerRenderer->file = "assets/mariss.bmp";
	AnimatedEntityRenderer->file = "assets/ass.bmp";

	BackgroundRenderer->file = "assets/background_black.bmp";

	FloorRenderer->file = "assets/floor.bmp";
	Animation->frameDuration = 1.0;

	Animation->renderer = AnimatedEntityRenderer;

	Scene->Camera->AddBehaviour(BackgroundRenderer);
	Player->AddBehaviour(PlayerRenderer);
	Player->AddBehaviour(PlayerPhysics);
	Player->AddBehaviour(PlayerMovement);
	AnimatedEntity->AddBehaviour(AnimatedEntityRenderer);
	AnimatedEntity->AddBehaviour(Animation);

	Floor->AddBehaviour(FloorRenderer);
	Floor->AddBehaviour(FloorPhysics);
	Scene->AddEntity(Floor);
	Scene->AddEntity(AnimatedEntity);
	Scene->AddEntity(Player);

	Game::icon = "assets/icon.bmp";

	Game::SetActiveScene(Scene);
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