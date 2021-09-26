#include "physicsStatic.h"

#define PIXELS_PER_METERS 100

void BigNgine::PhysicsStaticBehaviour::Start()
{
	staticBodyDef.position.Set((parent->position.x + parent->size.x / 2) / PIXELS_PER_METERS,(parent->position.y + parent->size.y / 2) / PIXELS_PER_METERS);

	staticBody = parent->GetParentScene()->world->CreateBody(&staticBodyDef);

	staticBox.SetAsBox(parent->size.x / 2 / PIXELS_PER_METERS, parent->size.y / 2 / PIXELS_PER_METERS);

	staticBody->CreateFixture(&staticBox, 0.0f);
}

void BigNgine::PhysicsStaticBehaviour::Update(int deltaTime)
{
	
}

void BigNgine::PhysicsStaticBehaviour::Destroy()
{
	staticBody = nullptr;
}