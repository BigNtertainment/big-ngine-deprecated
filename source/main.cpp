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

BigNgine::Scene* Scene;

BigNgine::Entity* box;

void Start()
{
	Game::icon = "assets/icon.bmp";

	BigNgine::RendererBehaviour* BackgroundRenderer = new BigNgine::RendererBehaviour();
	Scene = new BigNgine::Scene();
	BackgroundRenderer->file = "assets/background.bmp";
	Scene->Camera->AddBehaviour(BackgroundRenderer);


	box = new BigNgine::Entity;
	BigNgine::RendererBehaviour* BOXrender = new BigNgine::RendererBehaviour;
	BigNgine::PhysicsBehaviour* BOXphys = new BigNgine::PhysicsBehaviour;

	BOXrender->file = "assets/mariss.bmp";
	box->size = BigNgine::Vector2(100.0f, 100.0f);
	box->position = BigNgine::Vector2(100.0f, 100.0f);

	box->AddBehaviour(BOXphys);
	box->AddBehaviour(BOXrender);

	Scene->AddEntity(box);
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