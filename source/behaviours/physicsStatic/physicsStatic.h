#pragma once
#include "../../types/behaviour/behaviour.h"
#include "box2d/box2d.h"

namespace BigNgine
{
	class PhysicsStaticBehaviour : public Behaviour
	{
	public:
		void Start() override;

		void Update(int deltaTime) override;

		void Destroy() override;
	
	private:
		b2BodyDef staticBodyDef;

		b2Body* staticBody;

		b2PolygonShape staticBox;
	};

}