#include <cmath>
#include "global/logger/logger.h"
#include "global/game/game.h"
#include "global/input/input.h"
#include "global/fileSystem/fileSystem.h"
#include "types/entity/entity.h"
#include "types/scene/scene.h"
#include "types/behaviour/behaviour.h"
#include "behaviours/follow/follow.h"
#include "behaviours/renderer/renderer.h"
#include "behaviours/physicsStatic/physicsStatic.h"
#include "behaviours/physics/physics.h"
#include "behaviours/platformerMovement/platformerMovement.h"
#include "behaviours/follow/follow.h"


BigNgine::Scene *Scene;
BigNgine::Scene *Scene2;

BigNgine::Entity *Player;
BigNgine::Entity *Ground;
BigNgine::Entity *Wall;
BigNgine::Entity *GRID;
BigNgine::Entity *sky;

Input::Callback *coolCallback;

void coolCallbackFunc(int key, int scancode, int mods)
{
	if (key == BIGNGINE_KEY_W)
	{
		Game::ChangeActiveScene(Scene);
	} else if (key == BIGNGINE_KEY_Q)
	{
		Game::ChangeActiveScene(Scene2);
	}
}

void Start()
{
	//	Scene stuff
	Scene = new BigNgine::Scene();
	Scene2 = new BigNgine::Scene();
	
	////	Player or Marisa stuff
	Player = new BigNgine::Entity();
	auto *pRendererBehaviour = new BigNgine::TextureRendererBehaviour();
	auto *pPhysicsBehaviour = new BigNgine::PhysicsBehaviour();
	auto *pMovement = new BigNgine::PlatformerMovementBehaviour();
	pRendererBehaviour->SetTexture("assets/img/mariss.png");
	pPhysicsBehaviour->constraintRotation = true;
	Player->SetDefaultSize(BigNgine::Vector2(100.0f, 100.0f));
	Player->SetDefaultPosition(BigNgine::Vector2(100.0f, 100.0f));
	Player->SetDepth(0.0f);
	Player->AddBehaviour(pRendererBehaviour);
	Player->AddBehaviour(pPhysicsBehaviour);
	Player->AddBehaviour(pMovement);
	
	auto* FollowPlayer = new BigNgine::FollowBehaviour(Player, BigNgine::Vector2(50., 50.));
	FollowPlayer->lockRotation = true;

	Scene->Camera->AddBehaviour(FollowPlayer);

	//	Ground stuff
	Ground = new BigNgine::Entity();
	auto *GRenderer = new BigNgine::ShaderRendererBehaviour();
	auto *GPhysics = new BigNgine::PhysicsStaticBehaviour();
	GRenderer->SetFragShader(FileSystem::LoadFile("assets/shaders/frag/standard.glsl"));
	Ground->SetDefaultSize(BigNgine::Vector2(800.0f, 40.0f));
	Ground->SetDefaultPosition(BigNgine::Vector2(-500.0f, 300.0f));
	Ground->SetDepth(0.0f);
	Ground->AddBehaviour(GRenderer);
	Ground->AddBehaviour(GPhysics);
	
	// Wall stuff
	Wall = new BigNgine::Entity();
	auto *WRenderer = new BigNgine::ShaderRendererBehaviour();
	auto *WPhysics = new BigNgine::PhysicsStaticBehaviour();
	WRenderer->SetFragShader(FileSystem::LoadFile("assets/shaders/frag/standard.glsl"));
	Wall->SetDefaultSize(BigNgine::Vector2(100.0f, 100.0f));
	Wall->SetDefaultPosition(BigNgine::Vector2(.0f, .0f));
	Wall->SetDepth(0.0f);
	Wall->AddBehaviour(WRenderer);
	Wall->AddBehaviour(WPhysics);
	
	GRID = new BigNgine::Entity();
	auto *GRIDrenderer = new BigNgine::ShaderRendererBehaviour();
	GRIDrenderer->SetFragShader(FileSystem::LoadFile("assets/shaders/frag/grid.glsl"));
	GRIDrenderer->SetVertShader(FileSystem::LoadFile("assets/shaders/vert/debugBackground.glsl"));
	GRID->SetDefaultSize(BigNgine::Vector2((float) Game::width, (float) Game::height));
	GRID->SetDefaultPosition(BigNgine::Vector2(-600, -400));
	GRID->SetDepth(-0.5f);
	GRID->AddBehaviour(GRIDrenderer);
	
	sky = new BigNgine::Entity();
	auto *skyRenderer = new BigNgine::ShaderRendererBehaviour();
	skyRenderer->SetFragShader(FileSystem::LoadFile("assets/shaders/frag/sky.glsl"));
	sky->SetDefaultSize(BigNgine::Vector2((float) Game::width, (float) Game::height));
	sky->SetDefaultPosition(BigNgine::Vector2(-600, -400));
	sky->SetDepth(0.9f);
	sky->AddBehaviour(skyRenderer);
	
	// Input::Callback* coolCallback = new Input::Callback(
	// 	[](int key, int scancode, int mods) {
	// 		if(key == BIGNGINE_KEY_W) {
	// 			Logger::Log("hello :)");
	// 		}
	// 	}
	// );
	
	coolCallback = new Input::Callback(coolCallbackFunc);
	
	///	Adding stuff to Scene
	Scene2->AddEntity(sky);
	Scene->AddEntity(Wall);
	Scene->AddEntity(Player);
	Scene->AddEntity(Ground);
	Scene->AddEntity(GRID);
	Game::SetActiveScene(Scene);
}

void Update([[maybe_unused]]int deltaTime)
{
//	GRID->size.x = (float) Game::width;
//	GRID->size.y = (float) Game::height;
//	GRID->position.x = (float) -Game::width / 2;
//	GRID->position.y = (float) -Game::height / 2;
//	Scene->Camera->position = BigNgine::Vector2(100.0,100.0);

}

int main([[maybe_unused]] int argc, [[maybe_unused]] char *args[])
{
	Game::width = 1200;
	Game::height = 800;
	Game::Name = "BigNgine";
	Game::icon = "assets/icon/icon.png";
	try
	{
		Game::Start(Start, Update);
	}
	catch (std::exception &e)
	{
		Logger::Error(e.what());
	}
	
	return 0;
}