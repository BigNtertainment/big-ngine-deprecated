#pragma once

#include "../../types/behaviour/behaviour.h"
#include "../physics/physics.h"
#include <vector>

namespace BigNgine {
	class PlatformerMovementBehaviour : public Behaviour {
	public:
		float speed;
		float jumpForce;
		int jumpCheckPrecision;
		float coyoteTime;

		PlatformerMovementBehaviour();
		PlatformerMovementBehaviour(float _speed);
		PlatformerMovementBehaviour(float _speed, float _jumpForce);
		PlatformerMovementBehaviour(float _speed, float _jumpForce, int _jumpCheckPrecision);
		PlatformerMovementBehaviour(float _speed, float _jumpForce, int _jumpCheckPrecision, float _coyoteTime);

		void Start();
		void Update(int deltaTime);
		void Destroy();

	private:
		std::vector<PhysicsBehaviour*> physics;
	};
}