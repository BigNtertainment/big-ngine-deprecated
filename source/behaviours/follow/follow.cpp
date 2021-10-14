#include "follow.h"

#define PI 3.14159265

BigNgine::FollowBehaviour::FollowBehaviour(Entity* _followed) {
	followed = _followed;
	pivot = Vector2(0, 0);
}

BigNgine::FollowBehaviour::FollowBehaviour(Entity* _followed, const Vector2& _pivot) {
	followed = _followed;
	pivot = _pivot;
}

void BigNgine::FollowBehaviour::Update(int deltaTime) {
	if(lockRotation) {
		parent->position = followed->position + pivot;
		return;
	}

	parent->rotation = followed->rotation;
	float angle = parent->rotation * PI / 180.0;
	Vector2 point = followed->position + pivot;
	parent->position.x = cos(angle) * (point.x - followed->position.x) - sin(angle) * (point.y - followed->position.y) + followed->position.x;
	parent->position.y = sin(angle) * (point.x - followed->position.x) + cos(angle) * (point.y - followed->position.y) + followed->position.y;
}
