#pragma once

#include <vector>
#include "box2d/box2d.h"
#include "../entity/entity.h"

namespace BigNgine {
	class Entity;
	class Behaviour;
	
	struct Camera {
		BigNgine::Vector2 position;
		float zoom;
	};
	
	class Scene {
		friend Entity;
		friend Behaviour;
	public:
		Camera* Camera;

		b2Vec2* gravity;
		b2World* world;

		Scene();

		void AddEntity(Entity* entity);

		void Start();
		void Update(int deltaTime);
		void Destroy();

		~Scene();
		
		unsigned int activeTime = 0;

	private:
		std::vector<Entity*> entities;
	};
}