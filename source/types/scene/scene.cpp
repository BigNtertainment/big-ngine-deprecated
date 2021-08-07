#include "./scene.h"

BigNgine::Scene::Scene() {

}

void BigNgine::Scene::AddEntity(Entity* entity) {
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
