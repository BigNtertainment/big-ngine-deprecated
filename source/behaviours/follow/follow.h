#pragma once
#include "../../types/behaviour/behaviour.h"
#include "../../types/vector2/vector2.h"
#include <math.h>
#include "../../global/logger/logger.h"

namespace BigNgine
{
	class FollowBehaviour : public Behaviour
	{
	public:
		Entity* followed;
		Vector2 pivot;

		bool lockRotation = false;
	
/// 	This behaviour sets position of parent entity to position of the followed entity.
///		@param _followed This is entity to be followed.
		explicit FollowBehaviour(Entity* _followed);
/// 	This behaviour sets position of parent entity to position of the followed entity.
///		@param _followed This is entity to be followed.
///		@param _pivot Offset from position of followed entity.
		FollowBehaviour(Entity* _followed, const Vector2& _pivot);

		void Update(int deltaTime) override;
	};
}