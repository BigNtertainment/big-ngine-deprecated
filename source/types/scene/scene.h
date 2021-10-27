#pragma once

#include <vector>
#include <algorithm>
#include "box2d/box2d.h"
#include "glad.h"
#include <GLFW/glfw3.h>
#include "../entity/entity.h"
#include "../vector2/vector2.h"
#include "../../global/game/game.h"
#include "../../global/input/input.h"

// TODO: Add scene specific Start and Update to constructor as parameters. It can be used to restore scene default state when loading it. (I solved it woohoo!!!)

namespace Input {
	class Callback;
}

namespace BigNgine {
	class Entity;
	class Behaviour;
	
	class Scene {
		friend Entity;
		friend Behaviour;
	public:
		Entity* Camera;
		float CameraZoom;

		b2Vec2* gravity;
		b2World* world;

		Scene(void (*Start)(BigNgine::Scene*), void (*Update)(BigNgine::Scene*, int));

///		Adds entity to Scene
///		@param entity BigNgine::Entity entity to be added to scene
		void AddEntity(Entity* entity);

///		Adds callback to Scene
///		@param callback Input::Callback callback to be added to scene
		void AddCallback(Input::Callback* callback);

		int GetActiveTime();

		void Start();
		void Update(int deltaTime);
		void Destroy();

		~Scene();

		static std::vector<Scene*> scenes;

		std::vector<Input::Callback*> GetCallbacks();
	private:
		std::vector<Entity*> entities;
		std::vector<Input::Callback*> callbacks;

		void (*_Start)(BigNgine::Scene*);
		void (*_Update)(BigNgine::Scene*, int);
		
		unsigned int activeTime = 0;
	};
}