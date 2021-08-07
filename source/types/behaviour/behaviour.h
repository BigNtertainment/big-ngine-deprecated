#pragma once

#include "../entity/entity.h"
#include <string>

namespace BigNgine {
	class Entity;

	class Behaviour {
		friend Entity;
	public:
		std::string name = "Behaviour";

		virtual void Start() = 0;
		virtual void Update(int deltaTime) = 0;
		virtual void Destroy() = 0;

		Behaviour();
		~Behaviour();
	protected:
		Entity* parent;
	};
}
