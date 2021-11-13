#include "/animation.h"
#include "animation.h"


BigNgine::AnimationBehaviour::AnimationBehaviour(float _animationDuration) : animationDuration(_animationDuration) {}

void BigNgine::AnimationBehaviour::Start()
{
	_textureRenderer = parent->GetBehaviours<BigNgine::TextureRendererBehaviour>()[0];
	for(auto texturePath : texturePaths)
    {
        _textures.push_back(new BigNgine::Texture(texturePath));
    }
}

void BigNgine::AnimationBehaviour::Update(int deltaTime)
{
//	TODO(tymon): finish this
	animationTimer += (float)deltaTime / 1000.0f;
	if (animationTimer >= animationDuration)
	{
		animationTimer = 0.0f;
	}
/*    if(!_textures.empty())
    {
        _textureRenderer->SetTexture(_textures[_currentTexture]);
        _currentTexture++;
        if(_currentTexture >= _textures.size())
        {
            _currentTexture = 0;
        }
    }*/
	Logger::Log(animationTimer);
}

void BigNgine::AnimationBehaviour::Delete()
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

