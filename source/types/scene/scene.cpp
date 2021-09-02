#include "./scene.h"
#include "../vector2/vector2.h"
#include "../../global/game/game.h"

BigNgine::Scene::Scene() {
	Camera = new Entity();

	Camera->size = Vector2(Game::width, Game::height);

	AddEntity(Camera);
}

void BigNgine::Scene::AddEntity(Entity* entity) {
	entity->parentScene = this;

	entities.push_back(entity);
}

void BigNgine::Scene::Start() {
	gravity = new b2Vec2(0.0f, 9.81f);
	world = new b2World(*gravity);
	for(auto & entity : entities) {
		entity->Start();
	}
}

void BigNgine::Scene::Update(int deltaTime) {
	for(auto & entity : entities) {
		entity->Update(deltaTime);
	}
	int32 velocityIterations = 6;
	int32 positionIterations = 2;

	world->Step(deltaTime / 1000.0, velocityIterations, positionIterations);
}

void BigNgine::Scene::Destroy() {
	for(auto & entity : entities) {
		delete entity;
	}
	delete world;
}

BigNgine::Scene::~Scene() {
	Destroy();
}
