#pragma once

#include "../vector2/vector2.h"
#include "../behaviour/behaviour.h"
#include <vector>

namespace BigNgine {
	class Behaviour;

	class Entity {
		friend Behaviour;
	public:
		Entity();
		Entity(BigNgine::Vector2 _position);

		BigNgine::Vector2 position;

		void addBehaviour(Behaviour* behaviour);

		void Start();
		void Update(int deltaTime);

		~Entity();

		static std::vector<Entity*> entities;

	private:
		std::vector<Behaviour*> behaviours;
	};
}
