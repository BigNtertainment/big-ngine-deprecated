#include <cmath>
#include "BigNgine.h"


// BigNgine::Scene *Scene;

// BigNgine::Entity *Player;
// BigNgine::Entity *Ground;
// BigNgine::Entity *Wall;
// BigNgine::Entity *Grid;
// BigNgine::Entity *sky;

// Input::Callback* MovementFlip;

// void MovementFlipFunc(int key, int scancode, int mods) {
// 	if(key == BIGNGINE_KEY_A) {
// 		Player->GetBehaviours<BigNgine::TextureRendererBehaviour>()[0]->xFlipped = false;
// 	} else if(key == BIGNGINE_KEY_D) {
// 		Player->GetBehaviours<BigNgine::TextureRendererBehaviour>()[0]->xFlipped = true;
// 	}
// }

void Start()
{
	BigNgine::Scene* Scene = new BigNgine::Scene([](BigNgine::Scene* Scene) {
		// Add Player to the Scene

		auto* Player = new BigNgine::Entity(BigNgine::Vector2(100.0f, 100.0f), 0.0f, BigNgine::Vector2(100.0f, 100.0f));
		Player->SetDepth(0.0f);

		auto *pRendererBehaviour = new BigNgine::TextureRendererBehaviour();
		pRendererBehaviour->SetTexture("assets/img/mariss.png");

		auto *pPhysicsBehaviour = new BigNgine::PhysicsBehaviour();
		pPhysicsBehaviour->constraintRotation = false;

		auto *pMovement = new BigNgine::PlatformerMovementBehaviour();
		
		Player->AddBehaviour(pRendererBehaviour);
		Player->AddBehaviour(pPhysicsBehaviour);
		Player->AddBehaviour(pMovement);

		// Make Camera follow the Player

		auto* FollowPlayer = new BigNgine::FollowBehaviour(Player, BigNgine::Vector2(50., 50.));
		FollowPlayer->lockRotation = true;

		Scene->Camera->AddBehaviour(FollowPlayer);

		// Add a Debug Grid on top of the Camera

		auto *GridRenderer = new BigNgine::ShaderRendererBehaviour();

		GridRenderer->SetFragShader(FileSystem::LoadFile("assets/shaders/frag/grid.glsl"));
		GridRenderer->SetVertShader(FileSystem::LoadFile("assets/shaders/vert/debugBackground.glsl"));

		Scene->Camera->AddBehaviour(GridRenderer);

		// Add a Floor

		auto* Floor = new BigNgine::Entity(BigNgine::Vector2(-500.0f, 300.0f), 0.0f, BigNgine::Vector2(800.0f, 40.0f));
		Floor->SetDepth(0.0f);

		auto *FRenderer = new BigNgine::ShaderRendererBehaviour();
		FRenderer->SetFragShader(FileSystem::LoadFile("assets/shaders/frag/standard.glsl"));

		auto *FPhysics = new BigNgine::PhysicsStaticBehaviour();

		Floor->AddBehaviour(FRenderer);
		Floor->AddBehaviour(FPhysics);

		// Add a wall

		auto* Wall = new BigNgine::Entity(BigNgine::Vector2(0.0f, 0.0f), 0.0f, BigNgine::Vector2(69.f, 420.f));
		Wall->SetDepth(0.0f);

		auto *WRenderer = new BigNgine::ShaderRendererBehaviour();
		WRenderer->SetFragShader(FileSystem::LoadFile("assets/shaders/frag/standard.glsl"));

		auto *WPhysics = new BigNgine::PhysicsStaticBehaviour();

		Wall->AddBehaviour(WRenderer);
		Wall->AddBehaviour(WPhysics);
		
		// Add a Sky Background

		auto* Sky = new BigNgine::Entity(BigNgine::Vector2(-600, -400), 0.0f, BigNgine::Vector2(Game::width, Game::height));
		Sky->SetDepth(0.9f);

		auto *SkyRenderer = new BigNgine::ShaderRendererBehaviour();
		SkyRenderer->SetFragShader(FileSystem::LoadFile("assets/shaders/frag/sky.glsl"));

		Sky->AddBehaviour(SkyRenderer);

		Scene->AddEntity(Floor);
		Scene->AddEntity(Wall);
		Scene->AddEntity(Sky);
		Scene->AddEntity(Player);

		auto* funnyCallback = new Input::Callback([](int key, int scancode, int mods) {
			if(key == BIGNGINE_KEY_A) {
				Logger::Log("A");
			}
		});

		Scene->AddCallback(funnyCallback);
	},
	[](BigNgine::Scene* Scene, int deltaTime) {
		if(Input::Get(BIGNGINE_KEY_Z))
			Scene->CameraZoom -= (float)(deltaTime / 1000.0f);
		
		if(Input::Get(BIGNGINE_KEY_X))
			Scene->CameraZoom += (float)(deltaTime / 1000.0f);
	});
	
	// MovementFlip = new Input::Callback(MovementFlipFunc);

	Game::SetActiveScene(Scene);
}

void Update([[maybe_unused]]int deltaTime)
{
	// if(Input::Get(BIGNGINE_KEY_Z))
	// 	Scene->CameraZoom -= (float)(deltaTime / 1000.);
	
	// if(Input::Get(BIGNGINE_KEY_X))
	// 	Scene->CameraZoom += (float)(deltaTime / 1000.);

	Logger::Log(Cursor::GetPosition());
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char *args[])
{
	Game::width = 1200;
	Game::height = 800;
	Game::name = "BigNgine";
	Game::icon = "assets/icon/icon.png";
	
	Game::Start(Start, Update);

	return 0;
}