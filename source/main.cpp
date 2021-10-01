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
BigNgine::Entity* GRID;

void Start()
{
//	Scene stuff
	Scene = new BigNgine::Scene();

////	Player or Marisa stuff
	Player = new BigNgine::Entity();
	auto* pRendererBehaviour = new BigNgine::TextureRendererBehaviour();
	auto* pPhysicsBehaviour = new BigNgine::PhysicsBehaviour();
	pRendererBehaviour->setFile("assets/img/mariss.png");
	pPhysicsBehaviour->constraintRotation = false;
	Player->SetDefaultSize(BigNgine::Vector2(100.0f, 100.0f));
	Player->SetDefaultPosition(BigNgine::Vector2(100.0f, 100.0f));
	Player->SetDepth(0.0f);
	Player->AddBehaviour(pRendererBehaviour);
	Player->AddBehaviour(pPhysicsBehaviour);

//	Ground stuff
	Ground = new BigNgine::Entity();
	auto* GRenderer = new BigNgine::ShaderRendererBehaviour();
	auto* GPhysics = new BigNgine::PhysicsStaticBehaviour();
	GRenderer->SetFragShader(FileSystem::LoadFile("assets/shaders/frag/standard.glsl"));
	Ground->SetDefaultSize(BigNgine::Vector2(800.0f, 40.0f));
	Ground->SetDefaultPosition(BigNgine::Vector2(-500.0f, 300.0f));
	Ground->SetDepth(0.0f);
	Ground->AddBehaviour(GRenderer);
	Ground->AddBehaviour(GPhysics);

// Wall stuff
	Wall = new BigNgine::Entity();
	auto* WRenderer = new BigNgine::ShaderRendererBehaviour();
	auto* WPhysics = new BigNgine::PhysicsStaticBehaviour();
	WRenderer->SetFragShader(FileSystem::LoadFile("assets/shaders/frag/standard.glsl"));
	Wall->SetDefaultSize(BigNgine::Vector2(100.0f, 100.0f));
	Wall->SetDefaultPosition(BigNgine::Vector2(-170.0f, 0.0));
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
	renderer2->setFile("assets/img/sztuka.png");
	Box2->SetDefaultSize(BigNgine::Vector2(300.0f, 300.0f));
	Box2->SetDefaultPosition(BigNgine::Vector2(532.0, 321.0f));
	Box2->SetDepth(0.0f);
	Box2->AddBehaviour(renderer2);
	
	GRID = new BigNgine::Entity();
	auto* GRIDrenderer = new BigNgine::ShaderRendererBehaviour();
	GRIDrenderer->SetFragShader(FileSystem::LoadFile("assets/shaders/frag/grid.glsl"));
	GRID->SetDefaultSize(BigNgine::Vector2(Game::width, Game::height));
	GRID->SetDefaultPosition(BigNgine::Vector2(-Game::width/2, -Game::height/2));
	GRID->SetDepth(-0.5f);
	GRID->AddBehaviour(GRIDrenderer);

///	Adding stuff to Scene
	Scene->AddEntity(Player);
	Scene->AddEntity(Ground);
	Scene->AddEntity(Wall);
	Scene->AddEntity(GRID);
	Game::SetActiveScene(Scene);
}

void Update(int deltaTime)
{
	GRID->size.x = Game::width;
	GRID->size.y = Game::height;
	GRID->position.x = -Game::width/2;
	GRID->position.y = -Game::height/2;
}

int main(int argc, char *args[])
{
	Game::width = 1200;
	Game::height = 800;
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