#pragma once

#include "../../types/behaviour/behaviour.h"
#include "../physics/physics.h"
#include "../../global/input/input.h"
#include <vector>

namespace BigNgine {
	class PlatformerMovementBehaviour : public Behaviour {
	public:
		float speed;
		float jumpForce;
		int jumpCheckPrecision;
		float coyoteTime;

		 int LeftButton = BIGNGINE_KEY_A;
		 int RightButton = BIGNGINE_KEY_D;
		 int JumpButton = BIGNGINE_KEY_SPACE;

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
		float jumpTimer;
	};
}