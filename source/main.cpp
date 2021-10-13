#include <cmath>
#include "external/Box2D/include/box2d/box2d.h"
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

BigNgine::Entity *Player;
BigNgine::Entity *Ground;
BigNgine::Entity *Wall;
BigNgine::Entity *Grid;
BigNgine::Entity *sky;

void Start()
{
	//	Scene stuff
	Scene = new BigNgine::Scene();
	
	////	Player or Marisa stuff
	Player = new BigNgine::Entity();
	auto *pRendererBehaviour = new BigNgine::TextureRendererBehaviour();
	auto *pPhysicsBehaviour = new BigNgine::PhysicsBehaviour();
	auto *pMovement = new BigNgine::PlatformerMovementBehaviour();
	pRendererBehaviour->setFile("assets/img/mariss.png");
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
	
	Grid = new BigNgine::Entity();
	auto *GridRenderer = new BigNgine::ShaderRendererBehaviour();
	GridRenderer->SetFragShader(FileSystem::LoadFile("assets/shaders/frag/grid.glsl"));
	GridRenderer->SetVertShader(FileSystem::LoadFile("assets/shaders/vert/debugBackground.glsl"));
	Grid->SetDefaultSize(BigNgine::Vector2((float) Game::width, (float) Game::height));
	Grid->SetDefaultPosition(BigNgine::Vector2(-600, -400));
	Grid->SetDepth(-0.5f);
	Grid->AddBehaviour(GridRenderer);
	
	sky = new BigNgine::Entity();
	auto *skyRenderer = new BigNgine::ShaderRendererBehaviour();
	skyRenderer->SetFragShader(FileSystem::LoadFile("assets/shaders/frag/sky.glsl"));
	sky->SetDefaultSize(BigNgine::Vector2((float) Game::width, (float) Game::height));
	sky->SetDefaultPosition(BigNgine::Vector2(-600, -400));
	sky->SetDepth(0.9f);
	sky->AddBehaviour(skyRenderer);
	
	///	Adding stuff to Scene
	Scene->AddEntity(Wall);
	Scene->AddEntity(Player);
	Scene->AddEntity(Ground);
	Scene->AddEntity(Grid);
	Game::SetActiveScene(Scene);
}

void Update([[maybe_unused]]int deltaTime)
{
	if(Input::Get(BIGNGINE_KEY_Z))
		Game::width -= deltaTime / 1000.0;

	//FIXME: It should make the window wider (spoiler: it doesn't)
	if(Input::Get(BIGNGINE_KEY_X))
		Game::width += deltaTime / 1000.0;
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char *args[])
{
	Game::width = 1200;
	Game::height = 800;
	Game::name = "BigNgine";
	Game::icon = "assets/icon/icon.png";
	try
	{
		Game::Start(Start, Update);
	}
	catch (std::exception &e)
	{
		Logger::Error(e.what());
	}

	delete Scene;

	return 0;
}