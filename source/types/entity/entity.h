#pragma once

#include "../vector2/vector2.h"
#include "../behaviour/behaviour.h"
#include "../scene/scene.h"
#include <vector>

namespace BigNgine {
	class Behaviour;
	class Scene;

	class Entity {
		friend Behaviour;
		friend Scene;
	public:
		Entity();
		Entity(BigNgine::Vector2 _position);

		BigNgine::Vector2 position;
		float rotation;

		void AddBehaviour(Behaviour* behaviour);

		void Start();
		void Update(int deltaTime);

		Scene* GetParentScene();

		~Entity();

	private:
		std::vector<Behaviour*> behaviours;
		Scene* parentScene;
	};
}
