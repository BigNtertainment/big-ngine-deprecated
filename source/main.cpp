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
// #include "behaviours/platformerMovement/platformerMovement.h"

#define FPS 80
#define SPEED 200

BigNgine::Scene* Scene;

BigNgine::Entity* Player;
BigNgine::Entity* Floor;

void Start()
{
	Scene = new BigNgine::Scene();

	Player = new BigNgine::Entity(BigNgine::Vector2(Game::width / 2.0f, 10.0f), 0.0f, BigNgine::Vector2(100.0f, 100.0f));
	Floor = new BigNgine::Entity(BigNgine::Vector2(0.0f, Game::height - 40.0f), 0.0f, BigNgine::Vector2(Game::width, 40.0f));

	BigNgine::RendererBehaviour* BackgroundRenderer = new BigNgine::RendererBehaviour();
	BigNgine::RendererBehaviour* PlayerRenderer = new BigNgine::RendererBehaviour();
	BigNgine::PhysicsBehaviour* PlayerPhysics = new BigNgine::PhysicsBehaviour();
	// BigNgine::PlatformerMovementBehaviour* PlayerMovement = new BigNgine::PlatformerMovementBehaviour(PlayerPhysics);
	BigNgine::RendererBehaviour* FloorRenderer = new BigNgine::RendererBehaviour();
	BigNgine::PhysicsStaticBehaviour* FloorPhysics = new BigNgine::PhysicsStaticBehaviour();

	BackgroundRenderer->file = "assets/background.bmp";
	PlayerRenderer->file = "assets/mariss.bmp";
	FloorRenderer->file = "assets/floor.bmp";

	Scene->Camera->AddBehaviour(BackgroundRenderer);
	Player->AddBehaviour(PlayerRenderer);
	Player->AddBehaviour(PlayerPhysics);
	// Player->AddBehaviour(PlayerMovement);
	Floor->AddBehaviour(FloorRenderer);
	Floor->AddBehaviour(FloorPhysics);

	Scene->AddEntity(Player);
	Scene->AddEntity(Floor);

	Game::icon = "assets/icon.bmp";

	Game::SetActiveScene(Scene);
}

void Update(int deltaTime)
{	
	std::vector<BigNgine::PhysicsBehaviour*> physics = Player->GetBehaviours<BigNgine::PhysicsBehaviour>();

	if(physics.size() > 0) {
		Logger::Log(physics[0]->GetNumber());
	}
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