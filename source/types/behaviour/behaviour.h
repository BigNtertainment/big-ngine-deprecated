#pragma once

#include "../entity/entity.h"
#include <string>
#include <algorithm>

namespace BigNgine {
	class Entity;

	class Behaviour {
		friend Entity;
	public:
		std::string name = "Behaviour";

		virtual void Start();
		virtual void Update(int deltaTime);
		virtual void Destroy();

		/**
		 * Enables the behaviour updating.
		 */
		void Enable();

		/**
		 * Disables the behaviour updating.
		 */
		void Disable();

		/**
		 * Set the behaviour to be enabled or disabled.
		 * 
		 * @param _active Whether the behaviour should be enabled.
		 */
		void SetActive(bool _active);

		Behaviour();
		~Behaviour();
	protected:
		Entity* parent;

		bool active = true;

		virtual void OnEnable();
		virtual void OnDisable();
	};
}
