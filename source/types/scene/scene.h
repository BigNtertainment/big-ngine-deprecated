#pragma once

#include <vector>
#include <Box2D/box2d.h>
#include "../entity/entity.h"

namespace BigNgine {
	class Entity;
	class Behaviour;
	
	class Scene {
		friend Entity;
		friend Behaviour;
	public:
		Entity* Camera;

		b2Vec2* gravity;
		b2World* world;

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