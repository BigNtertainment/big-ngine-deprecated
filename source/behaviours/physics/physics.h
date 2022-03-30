#pragma once

#include "../../types/behaviour/behaviour.h"
#include "box2d/box2d.h"

#define PIXELS_PER_METERS 100

namespace BigNgine {
	class PhysicsBehaviour : public Behaviour {
	protected:
		void Start() override;
		void Update(int deltaTime) override;
		void Destroy() override;

		void OnEnable() override;
		void OnDisable() override;

		virtual void _Start();
		virtual void _Update(int deltaTime);
		virtual void _Destroy();

		b2BodyDef bodyDef;
		b2Body* body;
		b2PolygonShape* bodyBox;
		b2FixtureDef* fixtureDef;

		static b2World* world;
		static b2Vec2* gravity;

	private:
		b2Fixture* fixture;

		static uint32_t instanceCount;
		static uint32_t updateCount;
		const int32 velocityIterations = 6;
		const int32 positionIterations = 2;
	};
}