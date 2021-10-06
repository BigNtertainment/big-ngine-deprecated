#include <cmath>
#include "external/Box2D/include/box2d/box2d.h"
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
#include "behaviours/platformerMovement/platformerMovement.h"


BigNgine::Scene* Scene;

BigNgine::Entity* Player;
BigNgine::Entity* Ground;
BigNgine::Entity* Wall;
BigNgine::Entity* Box;
BigNgine::Entity* Box2;
BigNgine::Entity* Background;

Input::Callback* coolCallback;

void coolCallbackFunc(int key, int scancode, int mods) {
	if(key == BIGNGINE_KEY_W) {
		Logger::Log("hello :)");
	} else if(key == BIGNGINE_KEY_Q) {
		coolCallback->active = false;
	}
}

void Start()
{
//	Scene stuff
//	auto* BackgroundRenderer = new BigNgine::RendererBehaviour();
	Scene = new BigNgine::Scene();
//	BackgroundRenderer->file = "assets/img/background.bmp";
//	Scene->Camera->AddBehaviour(BackgroundRenderer);


////	Player or Marisa stuff
	Player = new BigNgine::Entity();
	auto* pRendererBehaviour = new BigNgine::TextureRendererBehaviour();
	auto* pPhysicsBehaviour = new BigNgine::PhysicsBehaviour();
	auto* pMovement = new BigNgine::PlatformerMovementBehaviour();
	pRendererBehaviour->setFile("assets/img/mariss.png");
	pPhysicsBehaviour->constraintRotation = true;
	Player->SetDefaultSize(BigNgine::Vector2(100.0f, 100.0f));
	Player->SetDefaultPosition(BigNgine::Vector2(600.0f, 0.0f));
	Player->SetDepth(-0.5f);
	Player->AddBehaviour(pRendererBehaviour);
	Player->AddBehaviour(pPhysicsBehaviour);
	Player->AddBehaviour(pMovement);

//	Ground stuff
	Ground = new BigNgine::Entity();
	auto* GRenderer = new BigNgine::ShaderRendererBehaviour();
	auto* GPhysics = new BigNgine::PhysicsStaticBehaviour();
	GRenderer->SetFragShader(FileSystem::LoadFile("assets/shaders/frag/standard.glsl"));
	Ground->SetDefaultSize(BigNgine::Vector2(640.0f, 40.0f));
	Ground->SetDefaultPosition(BigNgine::Vector2(0.0f, 700.0f));
	Ground->SetDepth(0.0f);
	Ground->AddBehaviour(GRenderer);
	Ground->AddBehaviour(GPhysics);

// Wall stuff
	Wall = new BigNgine::Entity();
	auto* WRenderer = new BigNgine::ShaderRendererBehaviour();
	auto* WPhysics = new BigNgine::PhysicsStaticBehaviour();
	WRenderer->SetFragShader(FileSystem::LoadFile("assets/shaders/frag/standard.glsl"));
	Wall->SetDefaultSize(BigNgine::Vector2(100.0f, 100.0f));
	Wall->SetDefaultPosition(BigNgine::Vector2(270.0f, 340.0f));
	Wall->SetDepth(0.0f);
	Wall->AddBehaviour(WRenderer);
	Wall->AddBehaviour(WPhysics);


	
//	====================================

	
	Box = new BigNgine::Entity();
	
	auto* renderer = new BigNgine::ShaderRendererBehaviour();

	renderer->SetFragShader(FileSystem::LoadFile("assets/shaders/frag/standard.glsl"));
	Box->SetDefaultSize(BigNgine::Vector2(100.0f, 100.0f));
	Box->SetDefaultPosition(BigNgine::Vector2(0.0f, 0.0f));
	Box->SetDepth(-0.5f);
	Box->AddBehaviour(renderer);

	Box2 = new BigNgine::Entity();
	auto* renderer2 = new BigNgine::TextureRendererBehaviour();
	Box2->SetDefaultSize(BigNgine::Vector2(300.0f, 300.0f));
	Box2->SetDefaultPosition(BigNgine::Vector2(532.0, 321.0f));
	renderer2->setFile("assets/img/szutka.png");
	Box2->SetDepth(0.0f);
	Box2->AddBehaviour(renderer2);
	
	Background = new BigNgine::Entity();
	auto* renderer3 = new BigNgine::ShaderRendererBehaviour();
	renderer3->SetFragShader(FileSystem::LoadFile("assets/shaders/frag/grid.glsl"));
	Background->SetDefaultSize(BigNgine::Vector2(Game::width, Game::height));
	Background->SetDefaultPosition(BigNgine::Vector2(0.0f, 0.0f));
	Background->SetDepth(0.5f);
	Background->AddBehaviour(renderer3);

	// Input::Callback* coolCallback = new Input::Callback(
	// 	[](int key, int scancode, int mods) {
	// 		if(key == BIGNGINE_KEY_W) {
	// 			Logger::Log("hello :)");
	// 		}
	// 	}
	// );

	coolCallback = new Input::Callback(coolCallbackFunc);

///	Adding stuff to Scene
	Scene->AddEntity(Background);
	Scene->AddEntity(Player);
	Scene->AddEntity(Ground);
//	Scene->AddEntity(Wall);
	Scene->AddEntity(Box);
//	Scene->AddEntity(Box2);
	Game::SetActiveScene(Scene);
}

void Update(int deltaTime)
{
	Background->size.x = Game::width;
	Background->size.y = Game::height;
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