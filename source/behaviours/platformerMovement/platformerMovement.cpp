#include "platformerMovement.h"
#include "../../global/input/input.h"

#define DEFAULT_SPEED 150.0f
#define DEFAULT_JUMP_FORCE 4.0f
#define DEFAULT_JUMP_CHECK_PRECISION 5
#define DEFAULT_COYOTE_TIME 0.25f

BigNgine::PlatformerMovementBehaviour::PlatformerMovementBehaviour() : speed(DEFAULT_SPEED), jumpForce(DEFAULT_JUMP_FORCE), jumpCheckPrecision(DEFAULT_JUMP_CHECK_PRECISION), coyoteTime(DEFAULT_COYOTE_TIME) {}

BigNgine::PlatformerMovementBehaviour::PlatformerMovementBehaviour(float _speed) : speed(_speed), jumpForce(DEFAULT_JUMP_FORCE), jumpCheckPrecision(DEFAULT_JUMP_CHECK_PRECISION), coyoteTime(DEFAULT_COYOTE_TIME) {}

BigNgine::PlatformerMovementBehaviour::PlatformerMovementBehaviour(float _speed, float _jumpForce) : speed(_speed), jumpForce(_jumpForce), jumpCheckPrecision(DEFAULT_JUMP_CHECK_PRECISION), coyoteTime(DEFAULT_COYOTE_TIME) {}

BigNgine::PlatformerMovementBehaviour::PlatformerMovementBehaviour(float _speed, float _jumpForce, int _jumpCheckPrecision) : speed(_speed), jumpForce(_jumpForce), jumpCheckPrecision(_jumpCheckPrecision), coyoteTime(DEFAULT_COYOTE_TIME) {}

BigNgine::PlatformerMovementBehaviour::PlatformerMovementBehaviour(float _speed, float _jumpForce, int _jumpCheckPrecision, float _coyoteTime) : speed(_speed), jumpForce(_jumpForce), jumpCheckPrecision(_jumpCheckPrecision), coyoteTime(_coyoteTime) {}

void BigNgine::PlatformerMovementBehaviour::Start() {
	physics = parent->GetBehaviours<PhysicsBehaviour>();
}

void BigNgine::PlatformerMovementBehaviour::Update(int deltaTime) {
	float horizontalMovement = Input::Get(SDLK_d) - Input::Get(SDLK_a);

	for(PhysicsBehaviour* physicsBehaviour : physics)
		physicsBehaviour->MoveBy(Vector2(horizontalMovement * speed * deltaTime / 1000, 0.0f));
}

void BigNgine::PlatformerMovementBehaviour::Destroy() {

}
