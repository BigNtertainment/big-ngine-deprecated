#include "entity.h"
#include "../vector2/vector2.h"
#include "../behaviour/behaviour.h"
#include "../../global/logger/logger.h"

BigNgine::Entity::Entity() {
	defaultPosition = BigNgine::Vector2(0.0, 0.0);
	defaultRotation = 0;
	defaultSize = BigNgine::Vector2(1.0, 1.0);
}

BigNgine::Entity::Entity(BigNgine::Vector2 _position) {
	defaultPosition = _position;
	defaultRotation = 0;
	defaultSize = BigNgine::Vector2(1.0, 1.0);
}

BigNgine::Entity::Entity(BigNgine::Vector2 _position, float _rotation) {
	defaultPosition = _position;
	defaultRotation = _rotation;
	defaultSize = BigNgine::Vector2(1.0, 1.0);
}

BigNgine::Entity::Entity(BigNgine::Vector2 _position, float _rotation, BigNgine::Vector2 _size) {
	defaultPosition = _position;
	defaultRotation = _rotation;
	defaultSize = _size;
}

void BigNgine::Entity::AddBehaviour(BigNgine::Behaviour* behaviour) {
	behaviour->parent = this;

	behaviours.push_back(behaviour);
}

void BigNgine::Entity::Start() {
	position = defaultPosition;
	rotation = defaultRotation;
	size = defaultSize;

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

void BigNgine::Entity::Destroy() {
	for(uint16_t i = 0; i < behaviours.size(); i++) {
		if(behaviours[i]->active) {
			behaviours[i]->Destroy();
		}
	}
}

BigNgine::Scene* BigNgine::Entity::GetParentScene() {
	return parentScene;
}

BigNgine::Entity::~Entity() {
	Destroy();
}
