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
	for(uint16_t i = 0; i < entities.size(); i++) {
		entities[i]->Start();
	}
}

void BigNgine::Scene::Update(int deltaTime) {
	for(uint16_t i = 0; i < entities.size(); i++) {
		entities[i]->Update(deltaTime);
	}
}

BigNgine::Scene::~Scene() {
	for(uint16_t i = 0; i < entities.size(); i++) {
		delete entities[i];
	}
}
