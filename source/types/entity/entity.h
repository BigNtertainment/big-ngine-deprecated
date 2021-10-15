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
		Entity(const BigNgine::Vector2& _defaultPosition);
		Entity(const BigNgine::Vector2& _defaultPosition, float _defaultRotation);
		Entity(const BigNgine::Vector2& _defaultPosition, float _defaultRotation, const BigNgine::Vector2& _defaultSize);

		BigNgine::Vector2 position;
		float rotation;
		BigNgine::Vector2 size;
		float depth;
		
///		Set default position of entity.
///		@param _position BigNgine::Vector2 with position
///		@important Origin of entity is its top left corner.
		void SetDefaultPosition(const Vector2& _position);
///		Set default rotation of entity.
///		@param _rotation float with rotation in degrees
///		@default 0 degrees
		void SetDefaultRotation(float _rotation);
///		Set default size of entity.
///		@param _size BigNgine::Vector2 with size of entity
		void SetDefaultSize(const Vector2& _size);
		
///		Set entities depth
///		@info the bigger the number the further the shit away
///		@param _depth float, SHOULD be between 0.0 and 1.0, it wont crash but
///		 it will be easier to implement in fragment shader
		void SetDepth(float _depth);

///		Add behaviour to entity
///		@param behaviour object that inherited form behaviour
		void AddBehaviour(Behaviour* behaviour);
///		Get behaviour from its type
///		@template behaviourType type of behaviour
///		@returns vector array with all behaviours of given type
		template<class behaviourType>
		std::vector<behaviourType*> GetBehaviours() {
			std::vector<behaviourType*> result;

			for(auto & behaviour : behaviours) {
				auto* cast = dynamic_cast<behaviourType*>(behaviour);

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
