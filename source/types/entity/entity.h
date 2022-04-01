#pragma once

#include <vector>
#include "../vector2/vector2.h"
#include "../behaviour/behaviour.h"
#include "../scene/scene.h"
#include "../../global/logger/logger.h"

#define DEFAULT_POSITION BigNgine::Vector2(0.0, 0.0)
#define DEFAULT_ROTATION 0.0
#define DEFAULT_SIZE BigNgine::Vector2(1.0, 1.0)

namespace BigNgine {
	class Behaviour;
	class Scene;

	class Entity {
		friend Behaviour;
		friend Scene;
	public:
		explicit Entity(const BigNgine::Vector2& _position = DEFAULT_POSITION, float _rotation = DEFAULT_ROTATION, const BigNgine::Vector2& _size = DEFAULT_SIZE);

		BigNgine::Vector2 position;
		float rotation;
		BigNgine::Vector2 size;
		float depth;
		
		///	Set entities depth
		///	@info the bigger the number the further the shit away
		///	@param _depth float, SHOULD be between 0.0 and 1.0, it wont crash but
		///	 it will be easier to implement in fragment shader
		void SetDepth(float _depth);

		///	Add behaviour to entity
		///	@param behaviour object that inherited form behaviour
		void AddBehaviour(Behaviour* behaviour);

		///	Get all behaviours of a given type
		///	@template behaviourType type of behaviour
		///	@returns vector array with all behaviours of given type
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

		// Get one behaviour of a given type
		// @template behaviourType type of behaviour
		// @returns behaviourType* pointer to behaviour of given type
		template<class behaviourType>
		behaviourType* GetBehaviour() {
			for(auto & behaviour : behaviours) {
				auto* cast = dynamic_cast<behaviourType*>(behaviour);

				if(cast != NULL) {
					return cast;
				}
			}

			return NULL;
		}

		void Start();
		void Update(int deltaTime);
		
		Scene* GetParentScene();

		~Entity();

	private:
		Scene* parentScene;
		std::vector<Behaviour*> behaviours;
	};
}
