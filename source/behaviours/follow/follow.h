#pragma once
#include "../../types/behaviour/behaviour.h"
#include "../../types/vector2/vector2.h"

namespace BigNgine
{
	//TODO: Add rotation support

	class FollowBehaviour : public Behaviour
	{
	public:
		Entity* followed;
		Vector2 pivot;

		bool lockRotation = false;

		FollowBehaviour(Entity* _followed);
		FollowBehaviour(Entity* _followed, Vector2 _pivot);

		void Update(int deltaTime);
	};
}