#include "entity.h"
#include "../vector2/vector2.h"
#include "../behaviour/behaviour.h"
#include "../../global/logger/logger.h"
#include <vector>
#include <algorithm>

std::vector<BigNgine::Entity*> BigNgine::Entity::entities;

BigNgine::Entity::Entity() {
	position = BigNgine::Vector2(0.0, 0.0);

	entities.push_back(this);
}

BigNgine::Entity::Entity(BigNgine::Vector2 _position) {
	position = _position;

	entities.push_back(this);
}

void BigNgine::Entity::addBehaviour(BigNgine::Behaviour* behaviour) {
	behaviour->parent = this;

	behaviours.push_back(behaviour);
}

void BigNgine::Entity::Start() {
	for(uint16_t i = 0; i < behaviours.size(); i++) {
		behaviours[i]->Start();
	}
}

void BigNgine::Entity::Update(int deltaTime) {
	for(uint16_t i = 0; i < behaviours.size(); i++) {
		behaviours[i]->Update(deltaTime);
	}
}

BigNgine::Entity::~Entity() {
	for(uint16_t i = 0; i < behaviours.size(); i++) {
		behaviours[i]->Destroy();
	}

	entities.erase(std::remove(entities.begin(), entities.end(), this), entities.end());
}
