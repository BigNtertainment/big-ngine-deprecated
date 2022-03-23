#pragma once
#include "../physics.h"
#include"../../global/logger/logger.h"

namespace BigNgine
{
	class PhysicsDynamicBehaviour : public PhysicsBehaviour
	{
	public:
		bool constraintX;
		bool constraintY;
		bool constraintRotation;

		void _Start() override;
		void _Update(int deltaTime) override;
		
		///	Moves parent entity to position passed by _target
		///	@param _target BigNgine::Vector2 with position
		void MoveTo(const BigNgine::Vector2& _target);
		///	Moves parent entity by offset passed by _offset
		///	@param _offset BigNgine::Vector2 with offset
		void MoveBy(const BigNgine::Vector2& _offset);
		///	Applies force to the center of parent entity
		///	@param force BigNgine::Vector2 with force
		void ApplyForce(const BigNgine::Vector2& force);

		/// Make it so the entity will not rotate (or revert the effect of this function)
		/// @param _constrain Whether the rotation should be constrained
		void ConstrainRotation(bool _constrain);
		/// Sets the density of the physics body
		/// @param density The density of the body
		void SetDensity(float density);
		/// Sets the friction of the physics body
		/// @param friction The friction of the body
		void SetFriction(float friction);

		/// Checks if rotation is constrained
		/// @returns true if rotation is constrained
		bool IsRotationConstrained() const;
		/// Returns the density of the body
		float GetDensity() const;
		/// Returns the friction of the body
		float GetFriction() const;
		/// It does not check if entity is on the ground, it just returns true.
		///@returns true
		bool IsGrounded() const;
	};
}