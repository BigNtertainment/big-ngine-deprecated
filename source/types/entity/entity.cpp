#include "entity.h"
#include "../vector2/vector2.h"
#include "../behaviour/behaviour.h"
#include "../../global/logger/logger.h"

BigNgine::Entity::Entity() {
	position = BigNgine::Vector2(0.0, 0.0);
	rotation = 0;
	size = BigNgine::Vector2(1.0, 1.0);
}

BigNgine::Entity::Entity(BigNgine::Vector2 _position) {
	position = _position;
	rotation = 0;
	size = BigNgine::Vector2(1.0, 1.0);
}

BigNgine::Entity::Entity(BigNgine::Vector2 _position, float _rotation) {
	position = _position;
	rotation = _rotation;
	size = BigNgine::Vector2(1.0, 1.0);
}

BigNgine::Entity::Entity(BigNgine::Vector2 _position, float _rotation, BigNgine::Vector2 _size) {
	position = _position;
	rotation = _rotation;
	size = _size;
}

void BigNgine::Entity::AddBehaviour(BigNgine::Behaviour* behaviour) {
	behaviour->parent = this;

	behaviours.push_back(behaviour);
}

void BigNgine::Entity::Start() {
	for(uint16_t i = 0; i < behaviours.size(); i++) {
		if(behaviours[i]->active) {
			behaviours[i]->Start();
		}
	}
}

void BigNgine::Entity::Update(int deltaTime) {
	for(uint16_t i = 0; i < behaviours.size(); i++) {
		if(behaviours[i]->active) {
			behaviours[i]->Update(deltaTime);
		}
	}
}

BigNgine::Scene* BigNgine::Entity::GetParentScene() {
	return parentScene;
}

BigNgine::Entity::~Entity() {
	for(uint16_t i = 0; i < behaviours.size(); i++) {
		if(behaviours[i]->active) {
			behaviours[i]->Destroy();
		}
	}
}
