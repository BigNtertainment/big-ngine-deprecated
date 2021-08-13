#include "physics.h"
#include"../../global/logger/logger.h"


#define PIXELS_PER_METERS 100

void BigNgine::PhysicsBehaviour::Start()
{
	//TODO: tymon zrob w koncu te constrainty
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set((parent->position.x + parent->size.x/2) / PIXELS_PER_METERS,(parent->position.y + parent->size.y/2) / PIXELS_PER_METERS);
//	rotation constrain
	if(constraintRotation)
		bodyDef.fixedRotation = true;

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
	parent->position.y = position.y * PIXELS_PER_METERS - parent->size.y/2;
}

void BigNgine::PhysicsBehaviour::Destroy() {
	body = nullptr;
}

void BigNgine::PhysicsBehaviour::MoveTo(BigNgine::Vector2 _target)
{
	float x = (_target.x + parent->size.x/2) / PIXELS_PER_METERS;
	float y = (_target.y + parent->size.y/2) / PIXELS_PER_METERS;
	parent->position.x = x * PIXELS_PER_METERS;
	parent->position.y = y * PIXELS_PER_METERS;
	body->SetTransform(b2Vec2(x, y), 0.0f);
}

void BigNgine::PhysicsBehaviour::MoveBy(BigNgine::Vector2 _target)
{
	float x = (_target.x + parent->position.x) / PIXELS_PER_METERS;
	float y = (_target.y + parent->position.y) / PIXELS_PER_METERS;
	parent->position.x = x * PIXELS_PER_METERS;
	parent->position.y = y * PIXELS_PER_METERS;
	body->SetTransform(b2Vec2(x, y), 0.0f);
}