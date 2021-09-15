#pragma once

#include "../vector2/vector2.h"
#include "../behaviour/behaviour.h"
#include "../scene/scene.h"
#include "../../global/logger/logger.h"
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
		float depth;
		
//		TODO: this is shit
		float TIME;

		void SetDefaultPosition(Vector2 _position);
		void SetDefaultRotation(float _rotation);
		void SetDefaultSize(Vector2 _size);
		
		///Set entities depth
		///@info the bigger the number the further the shit away
		///@param _depth float, SHOULD be between 0.0 and 1.0, it wont crash but
		/// it will be easier to implement in fragment shader
		void SetDepth(float _depth);

		void AddBehaviour(Behaviour* behaviour);
		template<class T>
		std::vector<T*> GetBehaviours() {
			std::vector<T*> result;

			for(uint16_t i = 0; i < behaviours.size(); i++) {
				T* cast = dynamic_cast<T*>(behaviours[i]);

				if(cast != NULL) {
					result.push_back(cast);
				}
			}

			return result;
		}

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
