#pragma once

#include "../entity/entity.h"

namespace BigNgine {
	class Entity;

	class Prefab {
	public:
		///	Creates a new instance of the prefab.
		///	@returns BigNgine::Entity* The new instance.
		virtual Entity* Create(void* args[]) = 0;
	};
}