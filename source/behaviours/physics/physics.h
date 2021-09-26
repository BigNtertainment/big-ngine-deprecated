#pragma once
#include "../../types/behaviour/behaviour.h"
#include"../../global/logger/logger.h"
#include "box2d/box2d.h"

namespace BigNgine
{
	class PhysicsBehaviour : public Behaviour
	{
	public:
		bool constraintX;
		bool constraintY;
		bool constraintRotation;

		int GetNumber() {
			return 5;
		}

		void Start();

		void Update(int deltaTime);

		void Destroy();
		
		void MoveTo(const BigNgine::Vector2& _target);
		void MoveBy(const BigNgine::Vector2& _target);
		void ApplyForce(const BigNgine::Vector2& force);
		
		/// it does not check if entity is on the ground it just returns true
		///@param NONE
		///@returns true
		bool IsGrounded();

	private:
		b2BodyDef bodyDef;

		b2Body* body;

		b2PolygonShape dynamicBox;

		b2FixtureDef fixtureDef;
		
		
		bool isGrounded;
	};
}