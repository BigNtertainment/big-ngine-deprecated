// #include "platformerMovement.h"
// #include "../../global/input/input.h"

// #define DEFAULT_SPEED 4.0f
// #define DEFAULT_JUMP_FORCE 4.0f
// #define DEFAULT_JUMP_CHECK_PRECISION 5
// #define DEFAULT_COYOTE_TIME 0.25f

// BigNgine::PlatformerMovementBehaviour::PlatformerMovementBehaviour(PhysicsBehaviour* _physics) : physics(_physics), speed(DEFAULT_SPEED), jumpForce(DEFAULT_JUMP_FORCE), jumpCheckPrecision(DEFAULT_JUMP_CHECK_PRECISION), coyoteTime(DEFAULT_COYOTE_TIME) {}

// BigNgine::PlatformerMovementBehaviour::PlatformerMovementBehaviour(PhysicsBehaviour* _physics, float _speed) : physics(_physics), speed(_speed), jumpForce(DEFAULT_JUMP_FORCE), jumpCheckPrecision(DEFAULT_JUMP_CHECK_PRECISION), coyoteTime(DEFAULT_COYOTE_TIME) {}

// BigNgine::PlatformerMovementBehaviour::PlatformerMovementBehaviour(PhysicsBehaviour* _physics, float _speed, float _jumpForce) : physics(_physics), speed(_speed), jumpForce(_jumpForce), jumpCheckPrecision(DEFAULT_JUMP_CHECK_PRECISION), coyoteTime(DEFAULT_COYOTE_TIME) {}

// BigNgine::PlatformerMovementBehaviour::PlatformerMovementBehaviour(PhysicsBehaviour* _physics, float _speed, float _jumpForce, int _jumpCheckPrecision) : physics(_physics), speed(_speed), jumpForce(_jumpForce), jumpCheckPrecision(_jumpCheckPrecision), coyoteTime(DEFAULT_COYOTE_TIME) {}

// BigNgine::PlatformerMovementBehaviour::PlatformerMovementBehaviour(PhysicsBehaviour* _physics, float _speed, float _jumpForce, int _jumpCheckPrecision, float _coyoteTime) : physics(_physics), speed(_speed), jumpForce(_jumpForce), jumpCheckPrecision(_jumpCheckPrecision), coyoteTime(_coyoteTime) {}

// void BigNgine::PlatformerMovementBehaviour::Start() {

// }

// void BigNgine::PlatformerMovementBehaviour::Update(int deltaTime) {
// 	float horizontalMovement = Input::Get(SDLK_d) - Input::Get(SDLK_a);

// 	parent->position.x += horizontalMovement * speed * deltaTime / 1000;
// }

// void BigNgine::PlatformerMovementBehaviour::Destroy() {

// }
