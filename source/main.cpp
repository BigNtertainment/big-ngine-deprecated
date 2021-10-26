#include <cmath>
#include "BigNgine.h"


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
	
	///	Player or Marisa stuff
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
	Scene->AddEntity(sky);
	Scene->AddEntity(Wall);
	Scene->AddEntity(Player);
	Scene->AddEntity(Ground);
	Scene->AddEntity(Grid);
	Game::SetActiveScene(Scene);
}

void Update([[maybe_unused]]int deltaTime)
{
	if(Input::Get(BIGNGINE_KEY_Z))
		Scene->CameraZoom -= (float)(deltaTime / 1000.);
	
	if(Input::Get(BIGNGINE_KEY_X))
		Scene->CameraZoom += (float)(deltaTime / 1000.);

	Logger::Log(Cursor::GetPosition());
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char *args[])
{
	Game::width = 1200;
	Game::height = 800;
	Game::name = "BigNgine";
	Game::icon = "assets/icon/icon.png";
	
	Game::Start(Start, Update);

	delete Scene;

	return 0;
}