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

namespace BigNgine
{
	class Teleport : public Behaviour
	{
	public:
		PhysicsBehaviour* physics;
		
		void Start()
		{
		
		}
		
		void Update(int deltaTime)
		{
			if (Input::Get(SDLK_d))
			{
				physics->MoveBy(BigNgine::Vector2(10.0f, -10.0f));
				Logger::Log(parent->position.y);
			}
		}
		
		void Destroy()
		{
		
		}
	};
}


BigNgine::Scene* Scene;

BigNgine::Entity* box;

BigNgine::Entity* Ground;

void Start()
{
	auto* BackgroundRenderer = new BigNgine::RendererBehaviour();
	Scene = new BigNgine::Scene();
	BackgroundRenderer->file = "assets/background.bmp";
	Scene->Camera->AddBehaviour(BackgroundRenderer);


	box = new BigNgine::Entity();
	auto* pRendererBehaviour = new BigNgine::RendererBehaviour();
	auto* pPhysicsBehaviour = new BigNgine::PhysicsBehaviour();
	auto* pTeleport = new BigNgine::Teleport();
	pTeleport->physics = pPhysicsBehaviour;
	pRendererBehaviour->file = "assets/mariss.bmp";
	box->SetDefaultSize(BigNgine::Vector2(100.0f, 100.0f));
	box->SetDefaultPosition(BigNgine::Vector2(200.0f, 0.0f));
	box->AddBehaviour(pRendererBehaviour);
	box->AddBehaviour(pPhysicsBehaviour);
	box->AddBehaviour(pTeleport);
	
	Ground = new BigNgine::Entity();
	auto* GRenderer = new BigNgine::RendererBehaviour();
	auto* GPhysics = new BigNgine::PhysicsStaticBehaviour();
	GRenderer->file = "assets/floor.bmp";
	Ground->SetDefaultSize(BigNgine::Vector2(640.0f, 40.0f));
	Ground->SetDefaultPosition(BigNgine::Vector2(0.0f, 440.0f));
	Ground->AddBehaviour(GRenderer);
	Ground->AddBehaviour(GPhysics);

	Scene->AddEntity(box);
	Scene->AddEntity(Ground);
	Game::SetActiveScene(Scene);
}

void Update(int deltaTime)
{

}

int main(int argc, char *args[])
{
	Game::width *= 2;
	Game::height *= 2;
	Game::Name = "BigNgine";
	Game::icon = "assets/icon.bmp";
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