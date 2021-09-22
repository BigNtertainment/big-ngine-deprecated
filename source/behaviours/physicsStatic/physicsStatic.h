#pragma once
#include "../../types/behaviour/behaviour.h"
#include "box2d/box2d.h"

namespace BigNgine
{
	class PhysicsStaticBehaviour : public Behaviour
	{
	public:
		void Start();

		void Update(int deltaTime);

		void Destroy();
	
	private:
		b2BodyDef staticBodyDef;

		b2Body* staticBody;

		b2PolygonShape staticBox;
	};

}