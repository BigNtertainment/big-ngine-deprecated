#include "BigNgine.h"
#include <windows.h>

class Bullet : public BigNgine::Prefab {
public:
	BigNgine::Entity* Create(void* args[]) override {
		auto* result = new BigNgine::Entity(*(BigNgine::Vector2*)args[0], *(float*)args[1], *(BigNgine::Vector2*)args[2]);

		// Add necessary behaviours
		auto *bulletRenderer = new BigNgine::TextureRendererBehaviour();
		bulletRenderer->AddTexture("assets/img/mariss.png");

		auto *bulletPhysics = new BigNgine::PhysicsBehaviour();

		result->AddBehaviour(bulletRenderer);
		result->AddBehaviour(bulletPhysics);

		return result;
	}
};

auto *Scene = new BigNgine::Scene(
	[](BigNgine::Scene *Scene)
	{
		// Add Player to the Scene

		auto *Player = new BigNgine::Entity(BigNgine::Vector2(100.0f, 100.0f), 0.0f, BigNgine::Vector2(100.0f, 100.0f));
		Player->SetDepth(0.0f);
		
		auto *pRendererBehaviour = new BigNgine::TextureRendererBehaviour();
		pRendererBehaviour->AddTexture("assets/img/mariss_xmas.png");

		auto *pPhysicsBehaviour = new BigNgine::PhysicsBehaviour();
		pPhysicsBehaviour->constraintRotation = true;

		auto *pMovement = new BigNgine::PlatformerMovementBehaviour();

		Player->AddBehaviour(pRendererBehaviour);
		Player->AddBehaviour(pPhysicsBehaviour);
		Player->AddBehaviour(pMovement);
		
//			Christmas tree
		auto *christmas_tree = new BigNgine::Entity(BigNgine::Vector2(200.0f, 200.0f - 100), 0.0f, BigNgine::Vector2(75.0f * 2, 100.0f * 2));
		christmas_tree->SetDepth(0.5f);
		auto *christmas_tree_renderer = new BigNgine::TextureRendererBehaviour();
		christmas_tree_renderer->AddTexture("assets/img/mariss.png");
		auto* christmas_tree_animation = new BigNgine::AnimationBehaviour(2.f);
		christmas_tree_animation->AddTexture("assets/img/christmas_tree_1.png");
		christmas_tree_animation->AddTexture("assets/img/christmas_tree_2.png");
		
		
		christmas_tree->AddBehaviour(christmas_tree_renderer);
		christmas_tree->AddBehaviour(christmas_tree_animation);
		// Make Camera follow the Player

//			IMPORTANT(imustend): if i remember correctly, adding renderer to camera doesn't work, but i don't remember why
		auto *FollowPlayer = new BigNgine::FollowBehaviour(Player, BigNgine::Vector2(50., 50.));
		FollowPlayer->lockRotation = true;

		Scene->Camera->AddBehaviour(FollowPlayer);
		Scene->Camera->SetDepth(.5f);

		//add floor
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

		auto *Floor2 = new BigNgine::Entity(BigNgine::Vector2(300.f, 300.f), 0.0f,
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
		BigNgine::Game* game = BigNgine::Game::GetInstance();

		auto *Sky = new BigNgine::Entity(
			BigNgine::Vector2(-600, -400), 0.0f,
			BigNgine::Vector2(
				game->GetWindowWidth(),
				game->GetWindowHeight()));

		Sky->SetDepth(0.9f);

		auto *SkyRenderer = new BigNgine::ShaderRendererBehaviour();
		SkyRenderer->SetFragShader(
			FileSystem::LoadFile("assets/shaders/frag/sky.glsl"));

		// sky follow camera :)
		auto *FollowCamera = new BigNgine::FollowBehaviour(
			Scene->Camera,
			BigNgine::Vector2(-600., -400.));

		Sky->AddBehaviour(FollowCamera);
		Sky->AddBehaviour(SkyRenderer);

		Scene->AddEntity(Floor);
		Scene->AddEntity(Floor2);
//			Scene->AddEntity(Wall);
		Scene->AddEntity(Sky);
		Scene->AddEntity(christmas_tree);
		Scene->AddEntity(Player);

		// TODO: Move this to player movement behaviour
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
			}
		);

		// It's bad :(
		auto shoot = new Input::Callback(
			[Player, Scene](int key, int scancode, int mods)
			{
				// On Q press
				if (key == BIGNGINE_KEY_Q)
				{
					// Create new bullet
					Bullet bullet;

					BigNgine::Vector2 position = Player->position + BigNgine::Vector2(
						0.f,
						20.f * (Player->GetBehaviour<BigNgine::TextureRendererBehaviour>()->xFlipped ? -1.f : 1.f)
					);
					float rotation = 0.f;
					BigNgine::Vector2 scale = BigNgine::Vector2(10.f, 10.f);
					float bulletForce = 10.f * (Player->GetBehaviour<BigNgine::TextureRendererBehaviour>()->xFlipped ? -1.f : 1.f);

					void* bulletData[] = {
						&position,
						&rotation,
						&scale
					};

					// Add bullet to scene
					Scene->AddPrefab(bullet, bulletData, [bulletForce](BigNgine::Entity* bulletEntity) {
						// Apply the force to the bullet after it has been added to the scene
						bulletEntity->GetBehaviour<BigNgine::PhysicsBehaviour>()->ApplyForce(BigNgine::Vector2(bulletForce, 0.f));
					});
				}
			}
		);

		Scene->AddCallback(flipTextureOnMovement);
		Scene->AddCallback(shoot);
	},
	[](BigNgine::Scene *Scene, int deltaTime)
	{
		if (Input::Get(BIGNGINE_KEY_Z))
			Scene->CameraZoom -= ((float)deltaTime / 1000.0f);

		if (Input::Get(BIGNGINE_KEY_X))
			Scene->CameraZoom += ((float)deltaTime / 1000.0f);
	}
);

void Start()
{
	Logger::Log("Start.");
	Logger::Warn("Start?");
	Logger::Error("Start!");
}

void Update([[maybe_unused]] int deltaTime)
{
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char *args[])
{
	BigNgine::Game* game = BigNgine::Game::GetInstance();

	game->ResizeWindow(1200, 800);

	game->SetName("BigNgine");

	game->SetIcon("assets/icon/icon.png");

	Logger::Log("Starting game.");

	game->Start(Scene, Start, Update);

	return 0;
}