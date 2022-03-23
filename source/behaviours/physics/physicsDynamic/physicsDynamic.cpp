#include "physicsDynamic.h"
#include <iostream>

#define PI 3.14159265359

#define PIXELS_PER_METERS 100

void BigNgine::PhysicsDynamicBehaviour::_Start()
{
	bodyDef.type = b2_dynamicBody;
	bodyDef.fixedRotation = constraintRotation;

	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
}

void BigNgine::PhysicsDynamicBehaviour::_Update(int deltaTime)
{
	body->SetAwake(true);

	b2Vec2 position = body->GetPosition();

	parent->rotation = body->GetAngle() * 180.0 / PI;
	parent->position.x = position.x * PIXELS_PER_METERS - parent->size.x/2;
	parent->position.y = position.y * PIXELS_PER_METERS - parent->size.y/2;
}

void BigNgine::PhysicsDynamicBehaviour::MoveTo(const BigNgine::Vector2& _target)
{
	float x = (_target.x) / PIXELS_PER_METERS;
	float y = (_target.y) / PIXELS_PER_METERS;
	parent->position.x = x * PIXELS_PER_METERS;
	parent->position.y = y * PIXELS_PER_METERS;
	body->SetTransform(b2Vec2(x  + parent->size.x/2 / PIXELS_PER_METERS, y  + parent->size.y/2 / PIXELS_PER_METERS), body->GetAngle());
}

void BigNgine::PhysicsDynamicBehaviour::MoveBy(const BigNgine::Vector2& _offset)
{
	float x = (_offset.x + parent->position.x) / PIXELS_PER_METERS;
	float y = (_offset.y + parent->position.y) / PIXELS_PER_METERS;
	parent->position.x = x * PIXELS_PER_METERS;
	parent->position.y = y * PIXELS_PER_METERS;
	body->SetTransform(b2Vec2(x  + parent->size.y/2 / PIXELS_PER_METERS, y  + parent->size.y/2 / PIXELS_PER_METERS), body->GetAngle());
}

void BigNgine::PhysicsDynamicBehaviour::ApplyForce(const BigNgine::Vector2& force) {
	body->ApplyForceToCenter(b2Vec2(force.x, -force.y), true);
}

void BigNgine::PhysicsDynamicBehaviour::ConstrainRotation(bool _constrain) {
	bodyDef.fixedRotation = _constrain;
}

void BigNgine::PhysicsDynamicBehaviour::SetDensity(float density) {
	fixtureDef.density = density;
}

void BigNgine::PhysicsDynamicBehaviour::SetFriction(float friction) {
	fixtureDef.friction = friction;
}

bool BigNgine::PhysicsDynamicBehaviour::IsRotationConstrained() const {
	return bodyDef.fixedRotation;
}

float BigNgine::PhysicsDynamicBehaviour::GetDensity() const {
	return fixtureDef.density;
}

float BigNgine::PhysicsDynamicBehaviour::GetFriction() const {
	return fixtureDef.friction;
}

bool BigNgine::PhysicsDynamicBehaviour::IsGrounded() const {
	return true;
} 