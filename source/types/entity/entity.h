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
		Entity(BigNgine::Vector2 _defaultPosition);
		Entity(BigNgine::Vector2 _defaultPosition, float _defaultRotation);
		Entity(BigNgine::Vector2 _defaultPosition, float _defaultRotation, BigNgine::Vector2 _defaultSize);

		BigNgine::Vector2 position;
		float rotation;
		BigNgine::Vector2 size;

		void SetDefaultPosition(Vector2 _position);
		void SetDefaultRotation(float _rotation);
		void SetDefaultSize(Vector2 _size);

		void AddBehaviour(Behaviour* behaviour);

		void Start();
		void Update(int deltaTime);
		void Destroy();

		Scene* GetParentScene();

		~Entity();

	private:
		Scene* parentScene;
		std::vector<Behaviour*> behaviours;

		BigNgine::Vector2 defaultPosition;
		float defaultRotation;
		BigNgine::Vector2 defaultSize;
	};
}
