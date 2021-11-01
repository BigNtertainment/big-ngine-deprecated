#include <cmath>
#include "BigNgine.h"

class Rotate : public BigNgine::Behaviour {
	void Update(int deltaTime) {
		parent->rotation += deltaTime / 50.0;
	}
};

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
			if(key == BIGNGINE_KEY_Q) {
				Logger::Log("Q");
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

	BigNgine::Scene* StillDREScene = new BigNgine::Scene([](BigNgine::Scene* Scene) {
		auto* Player = new BigNgine::Entity(BigNgine::Vector2(-50.0f, -50.0f), 0.0f, BigNgine::Vector2(100.0f, 100.0f));
		Player->SetDepth(0.0f);

		auto* PlayerRotate = new Rotate();
		auto *pRendererBehaviour = new BigNgine::TextureRendererBehaviour();
		pRendererBehaviour->SetTexture("assets/img/mariss.png");

		Player->AddBehaviour(PlayerRotate);
		Player->AddBehaviour(pRendererBehaviour);

		Scene->AddEntity(Player);


		BigNgine::Sound* StillDre = new BigNgine::Sound();
		// Put your path here :)
		StillDre->OpenMP3("");

		StillDre->PlayOnLoop();

		auto* PauseCallback = new Input::Callback([StillDre](int key, int scancode, int mods) {
			switch(key) {
				case BIGNGINE_KEY_SPACE:
					if(StillDre->IsPaused())
						StillDre->Resume();
					else
						StillDre->Pause();
					break;

				case BIGNGINE_KEY_E:
					StillDre->SetVolume(StillDre->GetVolume() + 100);
					break;

				case BIGNGINE_KEY_Q:
					StillDre->SetVolume(StillDre->GetVolume() - 100);
					break;
			}
		});

		Scene->AddCallback(PauseCallback);
	},
	[](BigNgine::Scene* Scene, int deltaTime) {

	});

	Game::SetActiveScene(StillDREScene);
}

void Update([[maybe_unused]]int deltaTime)
{
	// Logger::Log(Cursor::GetPosition());
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