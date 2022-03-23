#include "physics.h"

uint32_t BigNgine::PhysicsBehaviour::instanceCount = 0;
uint32_t BigNgine::PhysicsBehaviour::updateCount = 0;
b2World* BigNgine::PhysicsBehaviour::world = nullptr;
b2Vec2* BigNgine::PhysicsBehaviour::gravity = nullptr;

void BigNgine::PhysicsBehaviour::Start()
{
	if(instanceCount == 0)
	{
		gravity = new b2Vec2(0.0f, 9.81f);
		world = new b2World(*gravity);
	}

	instanceCount++;

	bodyDef.position.Set((parent->position.x + parent->size.x / 2) / PIXELS_PER_METERS,(parent->position.y + parent->size.y / 2) / PIXELS_PER_METERS);

	body = world->CreateBody(&bodyDef);

	bodyBox.SetAsBox(parent->size.x / 2 / PIXELS_PER_METERS, parent->size.y / 2 / PIXELS_PER_METERS);

	fixtureDef.shape = &bodyBox;

	Logger::Log(1);

	body->CreateFixture(&fixtureDef);

	Logger::Log(2);

	_Start();
}

void BigNgine::PhysicsBehaviour::Update(int deltaTime)
{
	// Update the physics engine just once for all behaviours
	if(updateCount == 0)
		world->Step(deltaTime / 1000.0, velocityIterations, positionIterations);

	updateCount = (updateCount + 1) % instanceCount;

	_Update(deltaTime);
}

void BigNgine::PhysicsBehaviour::Destroy()
{
	body = nullptr;

	instanceCount--;

	if(instanceCount == 0)
	{
		delete world;
		delete gravity;
	}

	_Destroy();
}

void BigNgine::PhysicsBehaviour::_Start() {}
void BigNgine::PhysicsBehaviour::_Update(int deltaTime) {}
void BigNgine::PhysicsBehaviour::_Destroy() {}

void BigNgine::PhysicsBehaviour::OnEnable()
{
	body->SetAwake(true);
}

void BigNgine::PhysicsBehaviour::OnDisable()
{
	body->SetAwake(false);
}