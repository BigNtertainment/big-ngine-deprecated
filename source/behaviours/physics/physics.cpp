#include "physics.h"

#define PI 3.14159265359

#define PIXELS_PER_METERS 100

void BigNgine::PhysicsBehaviour::Start()
{
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set((parent->position.x + parent->size.x/2) / PIXELS_PER_METERS,(parent->position.y + parent->size.y/2) / PIXELS_PER_METERS);
//	rotation constrain
	bodyDef.fixedRotation = constraintRotation;

	body = parent->GetParentScene()->world->CreateBody(&bodyDef);

	dynamicBox.SetAsBox(parent->size.x/2 / PIXELS_PER_METERS, parent->size.y/2 / PIXELS_PER_METERS);

	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	body->CreateFixture(&fixtureDef);
}

void BigNgine::PhysicsBehaviour::Update(int deltaTime)
{
	body->SetAwake(true);

	b2Vec2 position = body->GetPosition();

	parent->rotation = body->GetAngle() * 180.0 / PI;
	parent->position.x = position.x * PIXELS_PER_METERS - parent->size.x/2;
	parent->position.y = position.y * PIXELS_PER_METERS - parent->size.y/2;
}

void BigNgine::PhysicsBehaviour::Destroy() {
	body = nullptr;
}

void BigNgine::PhysicsBehaviour::MoveTo(const BigNgine::Vector2& _target)
{
	float x = (_target.x) / PIXELS_PER_METERS;
	float y = (_target.y) / PIXELS_PER_METERS;
	parent->position.x = x * PIXELS_PER_METERS;
	parent->position.y = y * PIXELS_PER_METERS;
	body->SetTransform(b2Vec2(x  + parent->size.x/2 / PIXELS_PER_METERS, y  + parent->size.y/2 / PIXELS_PER_METERS), body->GetAngle());
}

void BigNgine::PhysicsBehaviour::MoveBy(const BigNgine::Vector2& _offset)
{
	float x = (_offset.x + parent->position.x) / PIXELS_PER_METERS;
	float y = (_offset.y + parent->position.y) / PIXELS_PER_METERS;
	parent->position.x = x * PIXELS_PER_METERS;
	parent->position.y = y * PIXELS_PER_METERS;
	body->SetTransform(b2Vec2(x  + parent->size.y/2 / PIXELS_PER_METERS, y  + parent->size.y/2 / PIXELS_PER_METERS), body->GetAngle());
}

void BigNgine::PhysicsBehaviour::ApplyForce(const BigNgine::Vector2& force) {
	body->ApplyForceToCenter(b2Vec2(force.x, -force.y), true);
}

bool BigNgine::PhysicsBehaviour::IsGrounded() {
	return true;
} 