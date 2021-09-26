#include "behaviour.h"

BigNgine::Behaviour::Behaviour() = default;

BigNgine::Behaviour::~Behaviour() {
	parent->behaviours.erase(std::remove(parent->behaviours.begin(), parent->behaviours.end(), this), parent->behaviours.end());
}

void BigNgine::Behaviour::Start() {}
void BigNgine::Behaviour::Update(int deltaTime) {}
void BigNgine::Behaviour::Destroy() {}
