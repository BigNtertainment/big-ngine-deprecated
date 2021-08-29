#include <SDL2/SDL.h>

#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
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
BigNgine::Entity* Box;
BigNgine::Entity* Box2;
BigNgine::Entity* Box3;

void Start()
{
//	Scene stuff
//	auto* BackgroundRenderer = new BigNgine::RendererBehaviour();
	Scene = new BigNgine::Scene();
//	BackgroundRenderer->file = "assets/img/background.bmp";
//	Scene->Camera->AddBehaviour(BackgroundRenderer);


////	Player or Marisa stuff
//	Player = new BigNgine::Entity();
//	auto* pRendererBehaviour = new BigNgine::RendererBehaviour();
//	auto* pPhysicsBehaviour = new BigNgine::PhysicsBehaviour();
//	auto* pMovement = new BigNgine::PlatformerMovementBehaviour();
//	pRendererBehaviour->file = "assets/img/mariss.bmp";
//	pPhysicsBehaviour->constraintRotation = true;
//	Player->SetDefaultSize(BigNgine::Vector2(100.0f, 100.0f));
//	Player->SetDefaultPosition(BigNgine::Vector2(200.0f, 0.0f));
//	Player->AddBehaviour(pRendererBehaviour);
//	Player->AddBehaviour(pPhysicsBehaviour);
//	Player->AddBehaviour(pMovement);
//
////	Ground stuff
//	Ground = new BigNgine::Entity();
//	auto* GRenderer = new BigNgine::RendererBehaviour();
//	auto* GPhysics = new BigNgine::PhysicsStaticBehaviour();
//	GRenderer->file = "assets/img/floor.bmp";
//	Ground->SetDefaultSize(BigNgine::Vector2(640.0f, 40.0f));
//	Ground->SetDefaultPosition(BigNgine::Vector2(0.0f, 800.0f));
//	Ground->AddBehaviour(GRenderer);
//	Ground->AddBehaviour(GPhysics);
//
//// Wall stuff
//	Wall = new BigNgine::Entity();
//	auto* WRenderer = new BigNgine::RendererBehaviour();
//	auto* WPhysics = new BigNgine::PhysicsStaticBehaviour();
//	WRenderer->file = "assets/img/mariss.bmp";
//	Wall->SetDefaultSize(BigNgine::Vector2(100.0f, 100.0f));
//	Wall->SetDefaultPosition(BigNgine::Vector2(270.0f, 340.0f));
//	Wall->AddBehaviour(WRenderer);
//	Wall->AddBehaviour(WPhysics);
//
//
	
//	====================================
	
	
	Box = new BigNgine::Entity();
	auto* renderer = new BigNgine::RendererBehaviour();
	renderer->vertShader = FileSystem::LoadFile("assets/shaders/vert/standard.glsl");
	renderer->fragShader = FileSystem::LoadFile("assets/shaders/frag/standard.glsl");
	renderer->depth = 2.0f;
	Box->SetDefaultSize(BigNgine::Vector2(100.0f, 100.0f));
	Box->SetDefaultPosition(BigNgine::Vector2(0.0f, 0.0f));
	Box->AddBehaviour(renderer);
	
	Box2 = new BigNgine::Entity();
	auto* renderer2 = new BigNgine::RendererBehaviour();
	renderer2->vertShader = FileSystem::LoadFile("assets/shaders/vert/standard.glsl");
	renderer2->fragShader = FileSystem::LoadFile("assets/shaders/frag/standard.glsl");
	renderer2->depth = 0.5f;
	Box2->SetDefaultSize(BigNgine::Vector2(200.0f, 300.0f));
	Box2->SetDefaultPosition(BigNgine::Vector2(980.0f, 100.0f));
	Box2->AddBehaviour(renderer2);
	
	Box3 = new BigNgine::Entity();
	auto* renderer3 = new BigNgine::RendererBehaviour();
	renderer3->vertShader = FileSystem::LoadFile("assets/shaders/vert/standard.glsl");
	renderer3->fragShader = FileSystem::LoadFile("assets/shaders/frag/grid.glsl");
	renderer3->depth = 0.0f;
	Box3->SetDefaultSize(BigNgine::Vector2(Game::width, Game::height));
	Box3->SetDefaultPosition(BigNgine::Vector2(0.0f, 0.0f));
	Box3->AddBehaviour(renderer3);

////	Adding stuff to Scene
//	Scene->AddEntity(Player);
//	Scene->AddEntity(Ground);
//	Scene->AddEntity(Wall);
//	Scene->AddEntity(Box);
	Scene->AddEntity(Box2);
	Scene->AddEntity(Box3);
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
	Game::icon = "assets/icon/icon.png";
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