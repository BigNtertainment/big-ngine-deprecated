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
		
		void Start() override;

		void Update(int deltaTime) override;

		void Destroy() override;
		
///		Moves parent entity to position passed by _target
///		@param _target BigNgine::Vector2 with position
		void MoveTo(const BigNgine::Vector2& _target);
///		Moves parent entity by offset passed by _offset
///		@param _offset BigNgine::Vector2 with offset
		void MoveBy(const BigNgine::Vector2& _offset);
///		Applies force to the center of parent entity
///		@param force BigNgine::Vector2 with force
		void ApplyForce(const BigNgine::Vector2& force);
		
		/// It does not check if entity is on the ground, it just returns true.
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