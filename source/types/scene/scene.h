#pragma once

#include <vector>
#include <algorithm>
#include <functional>
#include "box2d/box2d.h"
#include "glad.h"
#include <GLFW/glfw3.h>
#include "../entity/entity.h"
#include "../prefab/prefab.h"
#include "../vector2/vector2.h"
#include "../../global/game/game.h"
#include "../../global/input/input.h"

namespace BigNgine {
	class Scene;
}

typedef std::function<void(BigNgine::Scene*)> scene_startfunc;
typedef std::function<void(BigNgine::Scene*, int)> scene_updatefunc;

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

		Scene(scene_startfunc Start, scene_updatefunc Update);

		///	Adds entity to Scene
		///	@param entity BigNgine::Entity entity to be added to scene
		void AddEntity(Entity* entity);

		/// Creates entity from prefab and adds it to scene
		/// @param prefab the prefab to be added to the scene
		/// @param args arguments to be passed to prefab
		void AddPrefab(Prefab& prefab, void* args[] = {}, std::function<void(Entity* creation)> callback = [] (Entity* creation) {});

		///	Adds callback to Scene
		///	@param callback Input::Callback callback to be added to scene
		void AddCallback(Input::Callback* callback);

		void Start();
		void Update(int deltaTime);

		~Scene();

		static std::vector<Scene*> GetScenes();
		std::vector<Input::Callback*> GetCallbacks() const;
		int GetActiveTime() const;
	private:
		std::vector<Entity*> entities;
		std::vector<Input::Callback*> callbacks;

		static std::vector<Scene*> scenes;

		scene_startfunc _Start;
		scene_updatefunc _Update;
		
		unsigned int activeTime = 0;
	};
}