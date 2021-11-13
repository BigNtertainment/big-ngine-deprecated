#include <cmath>
#include "BigNgine.h"

void Start()
{
	auto *Scene = new BigNgine::Scene(
		[](BigNgine::Scene *Scene)
		{
			// Add Player to the Scene

			auto *Player = new BigNgine::Entity(BigNgine::Vector2(100.0f, 100.0f), 0.0f, BigNgine::Vector2(100.0f, 100.0f));
			Player->SetDepth(0.0f);

			
			auto *pAnimation = new BigNgine::AnimationBehaviour();
			auto *pRendererBehaviour = new BigNgine::TextureRendererBehaviour();
			pRendererBehaviour->AddTexture("assets/img/1.png");
			pAnimation->AddTexture("assets/img/1.png");
			pAnimation->AddTexture("assets/img/2.png");
			pAnimation->AddTexture("assets/img/3.png");
			pAnimation->AddTexture("assets/img/4.png");
			pAnimation->AddTexture("assets/img/5.png");
			pAnimation->AddTexture("assets/img/6.png");
			pAnimation->AddTexture("assets/img/7.png");
			pAnimation->AddTexture("assets/img/8.png");

			auto *pPhysicsBehaviour = new BigNgine::PhysicsBehaviour();
			pPhysicsBehaviour->constraintRotation = true;

			auto *pMovement = new BigNgine::PlatformerMovementBehaviour();

			Player->AddBehaviour(pAnimation);
			Player->AddBehaviour(pRendererBehaviour);
			Player->AddBehaviour(pPhysicsBehaviour);
			Player->AddBehaviour(pMovement);

			// Make Camera follow the Player

			auto *FollowPlayer = new BigNgine::FollowBehaviour(Player, BigNgine::Vector2(50., 50.));
			FollowPlayer->lockRotation = true;

			Scene->Camera->AddBehaviour(FollowPlayer);

			// Add a Debug Grid on top of the Camera
			//										  does not work

			auto *GridRenderer = new BigNgine::ShaderRendererBehaviour();

			GridRenderer->SetFragShader(
				FileSystem::LoadFile("assets/shaders/frag/grid.glsl"));
			GridRenderer->SetVertShader(
				FileSystem::LoadFile("assets/shaders/vert/debugBackground.glsl"));

			Scene->Camera->SetDepth(.5f);
			//										  FIXME(imustend): renderer on camera doesnt work
			Scene->Camera->AddBehaviour(GridRenderer);

			//										  add floor
			auto *Floor = new BigNgine::Entity(
				BigNgine::Vector2(-500.0f, 300.0f), 0.0f,
				BigNgine::Vector2(800.0f, 40.0f));
			Floor->SetDepth(0.0f);

			auto *FRenderer = new BigNgine::ShaderRendererBehaviour();
			FRenderer->SetFragShader(
				FileSystem::LoadFile("assets/shaders/frag/standard.glsl"));

			auto *FPhysics = new BigNgine::PhysicsStaticBehaviour();

			Floor->AddBehaviour(FRenderer);
			Floor->AddBehaviour(FPhysics);

			// Add a Floor2

			auto *Floor2 = new BigNgine::Entity(BigNgine::Vector2(300.f, 340.f), 0.0f,
												BigNgine::Vector2(600.0f, 40.0f));
			Floor2->SetDepth(0.0f);

			auto *FRenderer2 = new BigNgine::ShaderRendererBehaviour();
			FRenderer2->SetFragShader(
				FileSystem::LoadFile("assets/shaders/frag/standard.glsl"));

			auto *FPhysics2 = new BigNgine::PhysicsStaticBehaviour();

			Floor2->AddBehaviour(FRenderer2);
			Floor2->AddBehaviour(FPhysics2);

			// Add a wall

			auto *Wall = new BigNgine::Entity(
				BigNgine::Vector2(.0f, 200.f), 0.0f,
				BigNgine::Vector2(100.f, 100.f));
			Wall->SetDepth(0.0f);

			auto *WRenderer = new BigNgine::ShaderRendererBehaviour();
			WRenderer->SetFragShader(
				FileSystem::LoadFile("assets/shaders/frag/standard.glsl"));

			auto *WPhysics = new BigNgine::PhysicsStaticBehaviour();

			Wall->AddBehaviour(WRenderer);
			Wall->AddBehaviour(WPhysics);

			// Add a Sky Background
			//										  adding a 20 pixel margin bc we have some precision issues with follow camera behaviour
			auto *Sky = new BigNgine::Entity(
				BigNgine::Vector2(-610, -410), 0.0f,
				BigNgine::Vector2(
					(float)Game::width + 20,
					(float)Game::height + 20));

			Sky->SetDepth(0.9f);

			auto *SkyRenderer = new BigNgine::ShaderRendererBehaviour();
			SkyRenderer->SetFragShader(
				FileSystem::LoadFile("assets/shaders/frag/sky.glsl"));

			// sky follow camera :)
			auto *FollowCamera = new BigNgine::FollowBehaviour(
				Scene->Camera,
				BigNgine::Vector2(-610., -410.));

			Sky->AddBehaviour(SkyRenderer);
			Sky->AddBehaviour(FollowCamera);

			Scene->AddEntity(Floor);
			Scene->AddEntity(Floor2);
			Scene->AddEntity(Wall);
			Scene->AddEntity(Sky);
			Scene->AddEntity(Player);

			auto *flipTextureOnMovement = new Input::Callback(
				[Player](int key, int scancode, int mods)
				{
					if (key == BIGNGINE_KEY_A)
					{
						Player->GetBehaviours<BigNgine::TextureRendererBehaviour>()[0]->xFlipped = false;
					}
					else if (key == BIGNGINE_KEY_D)
					{
						Player->GetBehaviours<BigNgine::TextureRendererBehaviour>()[0]->xFlipped = true;
					}
				});

			Scene->AddCallback(flipTextureOnMovement);
		},
		[](BigNgine::Scene *Scene, int deltaTime)
		{
			if (Input::Get(BIGNGINE_KEY_Z))
				Scene->CameraZoom -= ((float)deltaTime / 1000.0f);

			if (Input::Get(BIGNGINE_KEY_X))
				Scene->CameraZoom += ((float)deltaTime / 1000.0f);
		});

	Game::SetActiveScene(Scene);
}

void Update([[maybe_unused]] int deltaTime)
{
	// mouse position debug
//	Logger::Log(Cursor::GetPosition());
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