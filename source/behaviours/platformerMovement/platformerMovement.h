#pragma once

#include "../../types/behaviour/behaviour.h"
#include "../physics/physics.h"

namespace BigNgine {
	class PlatformerMovementBehaviour : public Behaviour {
	public:
		float speed;
		float jumpForce;
		int jumpCheckPrecision;
		float coyoteTime;

		PlatformerMovementBehaviour(PhysicsBehaviour* _physics);
		PlatformerMovementBehaviour(PhysicsBehaviour* _physics, float _speed);
		PlatformerMovementBehaviour(PhysicsBehaviour* _physics, float _speed, float _jumpForce);
		PlatformerMovementBehaviour(PhysicsBehaviour* _physics, float _speed, float _jumpForce, int _jumpCheckPrecision);
		PlatformerMovementBehaviour(PhysicsBehaviour* _physics, float _speed, float _jumpForce, int _jumpCheckPrecision, float _coyoteTime);

		void Start();
		void Update(int deltaTime);
		void Destroy();

	private:
		PhysicsBehaviour* physics;
	};
}