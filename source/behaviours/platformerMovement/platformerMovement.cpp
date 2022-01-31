#include "platformerMovement.h"

BigNgine::PlatformerMovementBehaviour::PlatformerMovementBehaviour(float _speed, float _jumpForce, int _jumpCheckPrecision, float _coyoteTime) : speed(_speed), jumpForce(_jumpForce), jumpCheckPrecision(_jumpCheckPrecision), coyoteTime(_coyoteTime), jumpTimer(PLATFORMER_MOVEMENT_JUMP_TIMER) {}

void BigNgine::PlatformerMovementBehaviour::Start() {
	physics = parent->GetBehaviours<PhysicsBehaviour>();
	_jumpTimer = 0.0f;
}

void BigNgine::PlatformerMovementBehaviour::Update(int deltaTime) {
	// Moving horizontally
	auto horizontalMovement = (float)(Input::Get(RightButton) - Input::Get(LeftButton));

	// Jumping
	// TODO: Check if player is grounded
	bool jumping = Input::Get(JumpButton) && _jumpTimer <= 0.0f;

	for(PhysicsBehaviour* physicsBehaviour : physics) {
		if(horizontalMovement != 0.0)
//			physicsBehaviour->MoveBy(Vector2(horizontalMovement * speed * deltaTime / 1000, 0.0f));
			physicsBehaviour->ApplyForce(Vector2(horizontalMovement * speed * deltaTime / 1000, 0.0f));

		// TODO: Make jump force dependent on press length
		if(jumping) {
			_jumpTimer = jumpTimer;
			physicsBehaviour->ApplyForce(Vector2(0.0f, jumpForce));
		}
	}

	if(_jumpTimer > 0.0f)
		_jumpTimer -= (float)deltaTime / 1000.0f;
}

void BigNgine::PlatformerMovementBehaviour::Destroy() {

}
