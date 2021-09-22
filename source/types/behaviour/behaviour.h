#pragma once

#include "../entity/entity.h"
#include <string>
#include <algorithm>

namespace BigNgine {
	class Entity;

	class Behaviour {
		friend Entity;
	public:
		std::string name = "Behaviour";
		bool active = true;

		virtual void Start();
		virtual void Update(int deltaTime);
		virtual void Destroy();

		Behaviour();
		~Behaviour();
	protected:
		Entity* parent;
	};
}
