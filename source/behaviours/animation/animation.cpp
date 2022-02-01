#include "animation.h"


BigNgine::AnimationBehaviour::AnimationBehaviour(float _animationDuration) : animationDuration(_animationDuration) {}

void BigNgine::AnimationBehaviour::Start()
{
	_textureRenderer = parent->GetBehaviours<BigNgine::TextureRendererBehaviour>()[0];
	for(auto texturePath : texturePaths)
    {
        _textures.push_back(new BigNgine::Texture(texturePath));
    }

	frameDuration = animationDuration / (float)_textures.size();
	
//	letting the user know that animation has no textures in case of crash
//	would be nice to have proper error handling
	if(_textures.empty())
	{
		Logger::Error("Animation has no textures");
	}
}

void BigNgine::AnimationBehaviour::Update(int deltaTime)
{
//	yeah, this is a bit ugly, but it works
	animationTimer += (float)deltaTime / 1000.0f;
	if (animationTimer >= animationDuration)
	{
		animationTimer = 0.0f;
	}
	_textureRenderer->SetTexture(_textures[(int)(animationTimer / frameDuration)]);
}

void BigNgine::AnimationBehaviour::Destroy()
{
    for(auto texture : _textures)
    {
        delete texture;
    }
    _textures.clear();
}

void BigNgine::AnimationBehaviour::AddTexture(const char *texturePath)
{
	texturePaths.push_back(texturePath);
}

void BigNgine::AnimationBehaviour::setAnimationDuration(float _animationDuration)
{
	animationDuration = _animationDuration;
	animationTimer = animationDuration / (float)_textures.size();
}

