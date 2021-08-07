#pragma once

#include "../entity/entity.h"

namespace BigNgine {
	class Scene {
	public:
		Scene();

		void AddEntity(Entity* entity);

		void Start();
		void Update(int deltaTime);

		~Scene();

	private:
		std::vector<Entity*> entities;
	};
}