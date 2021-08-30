#include "follow.h"

BigNgine::FollowBehaviour::FollowBehaviour(Entity* _followed) {
	followed = _followed;
	pivot = Vector2(0, 0);
}

BigNgine::FollowBehaviour::FollowBehaviour(Entity* _followed, Vector2 _pivot) {
	followed = _followed;
	pivot = _pivot;
}

void BigNgine::FollowBehaviour::Update(int deltaTime) {
	parent->position = followed->position + pivot;
}
