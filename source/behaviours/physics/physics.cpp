#include "physics.h"
#include"../../global/logger/logger.h"

#include <Box2D/box2d.h>

#define PIXELS_PER_METERS 100

void BigNgine::PhysicsBehaviour::Start()
{
	//TODO: tymon zrob w koncu te constrainty
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set((parent->position.x + parent->size.x/2) / PIXELS_PER_METERS,(parent->position.y + parent->size.y/2) / PIXELS_PER_METERS);

	body = parent->GetParentScene()->world->CreateBody(&bodyDef);

	dynamicBox.SetAsBox(parent->size.x/2 / PIXELS_PER_METERS, parent->size.y/2 / PIXELS_PER_METERS);

	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;

	body->CreateFixture(&fixtureDef);
}

void BigNgine::PhysicsBehaviour::Update(int deltaTime)
{
	b2Vec2 position = body->GetPosition();
	
	parent->position.x = position.x * PIXELS_PER_METERS - parent->size.x/2;
	parent->position.y = position.y * PIXELS_PER_METERS- parent->size.y/2;
	Logger::Log(position.y * PIXELS_PER_METERS - parent->size.y/2);
}

void BigNgine::PhysicsBehaviour::Destroy() {
	body = nullptr;
}