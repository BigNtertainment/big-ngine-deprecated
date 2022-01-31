#pragma once

#include "../../types/behaviour/behaviour.h"
#include "../renderer/renderer.h"
#include <vector>

#define DEFAULT_ANIMATION_DURATION 1.0f

namespace BigNgine
{
	class AnimationBehaviour : public Behaviour
	{
	public:
		explicit AnimationBehaviour(float _animationDuration = DEFAULT_ANIMATION_DURATION);
		
		std::vector<const char *> texturePaths;

		void Start() override;
	
		void Update(int deltaTime) override;
	
		void Destroy() override;
		
		void AddTexture(const char *texturePath);
		
		void setAnimationDuration(float _animationDuration);
	
	private:
		BigNgine::TextureRendererBehaviour* _textureRenderer;
		std::vector<Texture*> _textures;
		float animationTimer;
		float animationDuration;
		float frameDuration;
	};
}