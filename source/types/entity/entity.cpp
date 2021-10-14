#include "entity.h"
#include "../../global/logger/logger.h"

BigNgine::Entity::Entity() {
	SetDefaultPosition(BigNgine::Vector2(0.0, 0.0));
	SetDefaultRotation(0);
	SetDefaultSize(BigNgine::Vector2(1.0, 1.0));
}

BigNgine::Entity::Entity(const BigNgine::Vector2& _position) {
	SetDefaultPosition(_position);
	SetDefaultRotation(0);
	SetDefaultSize(BigNgine::Vector2(1.0, 1.0));
}

BigNgine::Entity::Entity(const BigNgine::Vector2& _position, float _rotation) {
	SetDefaultPosition(_position);
	SetDefaultRotation(_rotation);
	SetDefaultSize(BigNgine::Vector2(1.0, 1.0));
}

BigNgine::Entity::Entity(const BigNgine::Vector2& _position, float _rotation, const BigNgine::Vector2& _size) {
	SetDefaultPosition(_position);
	SetDefaultRotation(_rotation);
	SetDefaultSize(_size);
}

void BigNgine::Entity::SetDefaultPosition(const BigNgine::Vector2& _position) {
	defaultPosition = _position;
	position = _position;
}

void BigNgine::Entity::SetDefaultRotation(float _rotation) {
	defaultRotation = _rotation;
	rotation = _rotation;
}

void BigNgine::Entity::SetDefaultSize(const BigNgine::Vector2& _size) {
	defaultSize = _size;
	size = _size;
}

void BigNgine::Entity::SetDepth(float _depth)
{
	depth = _depth;
}

void BigNgine::Entity::AddBehaviour(BigNgine::Behaviour* behaviour) {
	behaviour->parent = this;

	behaviours.push_back(behaviour);
}

void BigNgine::Entity::Start() {
	position = defaultPosition;
	rotation = defaultRotation;
	size = defaultSize;

	for(auto & behaviour : behaviours) {
		if(behaviour->active) {
			behaviour->Start();
		}
	}
}

void BigNgine::Entity::Update(int deltaTime) {
	for(auto & behaviour : behaviours) {
		if(behaviour->active) {
			behaviour->Update(deltaTime);
		}
	}
}

void BigNgine::Entity::Destroy() {
	for(auto & behaviour : behaviours) {
		if(behaviour->active) {
			behaviour->Destroy();
		}
	}
}

BigNgine::Scene* BigNgine::Entity::GetParentScene() {
	return parentScene;
}

BigNgine::Entity::~Entity() {
	Destroy();
}
