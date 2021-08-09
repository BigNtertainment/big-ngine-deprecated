#pragma once
#include "../../types/behaviour/behaviour.h"
#include "../renderer/renderer.h"

namespace BigNgine
{
	class AnimationBehaviour : public Behaviour
	{
	public:
		RendererBehaviour* renderer = nullptr;
		float frameDuration = 0.0;

		void Start();

		void Update(int deltaTime);

		void Destroy();

	private:
		int frameCount;
		int frame;
		float timer;
	};
}