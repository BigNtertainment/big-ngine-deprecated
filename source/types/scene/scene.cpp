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
	// TODO: make gravity setable
	gravity = new b2Vec2(0.0f, 9.81f);
	world = new b2World(*gravity);
	for(uint16_t i = 0; i < entities.size(); i++) {
		entities[i]->Start();
	}
}

void BigNgine::Scene::Update(int deltaTime) {
	for(uint16_t i = 0; i < entities.size(); i++) {
		entities[i]->Update(deltaTime);
	}
	int32 velocityIterations = 6;
	int32 positionIterations = 2;

	world->Step(deltaTime / 1000.0, velocityIterations, positionIterations);
}

void BigNgine::Scene::Destroy() {
	for(uint16_t i = 0; i < entities.size(); i++) {
		delete entities[i];
	}
	delete world;
}

BigNgine::Scene::~Scene() {
	Destroy();
}
