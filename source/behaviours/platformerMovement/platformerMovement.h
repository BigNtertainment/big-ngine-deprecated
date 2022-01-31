#pragma once

#include "../../types/behaviour/behaviour.h"
#include "../renderer/renderer.h"
#include "../physics/physics.h"
#include "../../global/input/input.h"
#include <vector>

#define PLATFORMER_MOVEMENT_DEFAULT_SPEED 450.0f
#define PLATFORMER_MOVEMENT_DEFAULT_JUMP_FORCE 300.0f
#define PLATFORMER_MOVEMENT_DEFAULT_JUMP_CHECK_PRECISION 5
#define PLATFORMER_MOVEMENT_DEFAULT_COYOTE_TIME 0.25f
#define PLATFORMER_MOVEMENT_JUMP_TIMER 0.5f

namespace BigNgine {
	class PlatformerMovementBehaviour : public Behaviour {
	public:
		float speed;
		float jumpForce;
		float jumpTimer;
		int jumpCheckPrecision;
		float coyoteTime;

		int LeftButton = BIGNGINE_KEY_A;
		int RightButton = BIGNGINE_KEY_D;
		int JumpButton = BIGNGINE_KEY_SPACE;

		PlatformerMovementBehaviour(float _speed = PLATFORMER_MOVEMENT_DEFAULT_SPEED, float _jumpForce = PLATFORMER_MOVEMENT_DEFAULT_JUMP_FORCE, int _jumpCheckPrecision = PLATFORMER_MOVEMENT_DEFAULT_JUMP_CHECK_PRECISION, float _coyoteTime = PLATFORMER_MOVEMENT_DEFAULT_COYOTE_TIME);

		void Start() override;
		void Update(int deltaTime) override;
		void Destroy() override;

	private:
		std::vector<PhysicsBehaviour*> physics;
		float _jumpTimer;
	};
}