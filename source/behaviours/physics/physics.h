#pragma once
#include "../../types/behaviour/behaviour.h"
#include <box2d/box2d.h>

namespace BigNgine
{
	class PhysicsBehaviour : public Behaviour
	{
	public:
		void Start();

		void Update(int deltaTime);

		void Destroy();
		
		void MoveTo(BigNgine::Vector2 _target);
		
		void MoveBy(BigNgine::Vector2 _target);
		
		bool RotationConstrain;
	
	private:
		b2BodyDef bodyDef;

		b2Body* body;

		b2PolygonShape dynamicBox;

		b2FixtureDef fixtureDef;
	};
}