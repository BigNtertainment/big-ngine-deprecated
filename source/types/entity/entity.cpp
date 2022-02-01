#include "entity.h"

BigNgine::Entity::Entity(const BigNgine::Vector2& _position, float _rotation, const BigNgine::Vector2& _size) : position(_position), rotation(_rotation), size(_size) {}


void BigNgine::Entity::SetDepth(float _depth)
{
	depth = _depth;
}

void BigNgine::Entity::AddBehaviour(BigNgine::Behaviour* behaviour) {
	behaviour->parent = this;

	behaviours.push_back(behaviour);
}

void BigNgine::Entity::Start() {
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

BigNgine::Scene* BigNgine::Entity::GetParentScene() {
	return parentScene;
}

BigNgine::Entity::~Entity() {
	for(auto & behaviour : behaviours) {
		delete behaviour;
	}
}
