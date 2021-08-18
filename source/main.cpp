#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_gpu.h>
#include <cmath>
#include <box2d/box2d.h>
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
#include "behaviours/platformerMovement/platformerMovement.h"


BigNgine::Scene* Scene;

BigNgine::Entity* Player;
BigNgine::Entity* Ground;
BigNgine::Entity* Wall;

void Start()
{
//	Scene stuff
	auto* BackgroundRenderer = new BigNgine::RendererBehaviour();
	Scene = new BigNgine::Scene();
	BackgroundRenderer->file = "assets/background_black.bmp";
	Scene->Camera->AddBehaviour(BackgroundRenderer);

//	Player or Marisa stuff
	Player = new BigNgine::Entity();
	auto* pRendererBehaviour = new BigNgine::RendererBehaviour();
	auto* pPhysicsBehaviour = new BigNgine::PhysicsBehaviour();
	auto* pMovement = new BigNgine::PlatformerMovementBehaviour();
	pRendererBehaviour->file = "assets/mariss.bmp";
	pPhysicsBehaviour->constraintRotation = true;
	Player->SetDefaultSize(BigNgine::Vector2(100.0f, 100.0f));
	Player->SetDefaultPosition(BigNgine::Vector2(200.0f, 0.0f));
	Player->AddBehaviour(pRendererBehaviour);
	Player->AddBehaviour(pPhysicsBehaviour);
	Player->AddBehaviour(pMovement);
	
//	Ground stuff
	Ground = new BigNgine::Entity();
	auto* GRenderer = new BigNgine::RendererBehaviour();
	auto* GPhysics = new BigNgine::PhysicsStaticBehaviour();
	GRenderer->file = "assets/floor.bmp";
	Ground->SetDefaultSize(BigNgine::Vector2(640.0f, 40.0f));
	Ground->SetDefaultPosition(BigNgine::Vector2(0.0f, 440.0f));
	Ground->AddBehaviour(GRenderer);
	Ground->AddBehaviour(GPhysics);

// Wall stuff
	Wall = new BigNgine::Entity();
	auto* WRenderer = new BigNgine::RendererBehaviour();
	auto* WPhysics = new BigNgine::PhysicsStaticBehaviour();
	WRenderer->file = "assets/mariss.bmp";
	Wall->SetDefaultSize(BigNgine::Vector2(100.0f, 100.0f));
	Wall->SetDefaultPosition(BigNgine::Vector2(270.0f, 340.0f));
	Wall->AddBehaviour(WRenderer);
	Wall->AddBehaviour(WPhysics);

//	Adding stuff to Scene
	Scene->AddEntity(Player);
	Scene->AddEntity(Ground);
	Scene->AddEntity(Wall);
	Game::SetActiveScene(Scene);
}

void Update(int deltaTime)
{
	
}

int main(int argc, char *args[])
{
	Game::width *= 2;
	Game::height *= 1.7;
	Game::Name = "BigNgine";
	Game::icon = "assets/icon.bmp";
	try
	{
		Game::Start(Start, Update);
	}
	catch (std::exception& e)
	{
		Logger::Error(e.what());
	}

	return 0;
}