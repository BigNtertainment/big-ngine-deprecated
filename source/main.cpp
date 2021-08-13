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
// #include "behaviours/platformerMovement/platformerMovement.h"

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
			if(parent->position.y > 480 && Input::GetMouse().LeftButton)
			{
				physics->MoveTo(BigNgine::Vector2(parent->position.x ,100.0f));
				physics->MoveBy(BigNgine::Vector2(20.0f, 0.0f));
			}
		}
		
		void Destroy()
		{
		
		}
	};
}


BigNgine::Scene* Scene;

BigNgine::Entity* box;
BigNgine::Entity* Floor;

void Start()
{
	auto* BackgroundRenderer = new BigNgine::RendererBehaviour();
	Scene = new BigNgine::Scene();
	BackgroundRenderer->file = "assets/background.bmp";
	Scene->Camera->AddBehaviour(BackgroundRenderer);

	BackgroundRenderer->file = "assets/background.bmp";

	box = new BigNgine::Entity;
	auto* pRendererBehaviour = new BigNgine::RendererBehaviour();
	auto* pPhysicsBehaviour = new BigNgine::PhysicsBehaviour();
	auto* pTeleport = new BigNgine::Teleport();
	
	pTeleport->physics = pPhysicsBehaviour;
	
	pRendererBehaviour->file = "assets/mariss.bmp";
	box->SetDefaultSize(BigNgine::Vector2(100.0f, 100.0f));
	box->SetDefaultSize(BigNgine::Vector2(100.0f, 100.0f));
	
	
	box->AddBehaviour(pRendererBehaviour);
	box->AddBehaviour(pTeleport);
	box->AddBehaviour(pPhysicsBehaviour);

	Game::SetActiveScene(Scene);
}

void Update(int deltaTime)
{	
	std::vector<BigNgine::PhysicsBehaviour*> physics = box->GetBehaviours<BigNgine::PhysicsBehaviour>();

	if(physics.size() > 0) {
		Logger::Log(physics[0]->GetNumber());
	}
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