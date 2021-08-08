#pragma once

#include <vector>
#include "../entity/entity.h"

namespace BigNgine {
	class Entity;

	class Scene {
	public:
		Entity* Camera;

		Scene();

		void AddEntity(Entity* entity);

		void Start();
		void Update(int deltaTime);
		void Destroy();

		~Scene();

	private:
		std::vector<Entity*> entities;
	};
}