#include "./scene.h"

std::vector<BigNgine::Scene *> BigNgine::Scene::scenes;

BigNgine::Scene::Scene(SceneStartFunction Start, SceneUpdateFunction Update)
{
	_Start = Start;
	_Update = Update;
	
	Scene::scenes.push_back(this);
}

void BigNgine::Scene::AddEntity(Entity *entity)
{
	// Set the entity parent scene
	entity->parentScene = this;
	
	// Add the entity to the scene entities vector
	entities.push_back(entity);
	
	// If this scene is currently running, call the entity start method
	if (Game::GetInstance()->GetActiveScene() == this)
		entity->Start();
}

void BigNgine::Scene::AddCallback(Input::Callback *callback)
{
	callbacks.push_back(callback);
}

std::vector<Input::Callback *> BigNgine::Scene::GetCallbacks()
{
	return callbacks;
}

int BigNgine::Scene::GetActiveTime()
{
	return activeTime;
}

void BigNgine::Scene::Start()
{
	gravity = new b2Vec2(0.0f, 9.81f);
	world = new b2World(*gravity);
	activeTime = 0;
	
	Camera = new BigNgine::Entity();
	CameraZoom = 1.0f;
	AddEntity(Camera);
	
	_Start(this);
	for (auto &entity: entities)
	{
		entity->Start();
	}
}

void BigNgine::Scene::Update(int deltaTime)
{
	int32 velocityIterations = 6;
	int32 positionIterations = 2;
	
	world->Step(deltaTime / 1000.0, velocityIterations, positionIterations);
	activeTime += deltaTime;
	
	_Update(this, deltaTime);
	for (auto &entity: entities)
	{
		entity->Update(deltaTime);
	}
}

BigNgine::Scene::~Scene()
{
	for (auto &entity: entities)
	{
		delete entity;
	}
	
	delete world;
	delete gravity;
	
	Scene::scenes.erase(std::remove(Scene::scenes.begin(), Scene::scenes.end(), this), Scene::scenes.end());
}

std::vector<BigNgine::Scene *> BigNgine::Scene::GetScenes()
{
	return BigNgine::Scene::scenes;
}