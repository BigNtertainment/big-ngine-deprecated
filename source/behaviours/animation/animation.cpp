#include "animation.h"

#include "../../global/logger/logger.h"

void BigNgine::AnimationBehaviour::Start() {
	if(renderer == nullptr) {
		Logger::Error("Frame duration not set or set to zero.");
		return;
	}

	frameCount = renderer->Surface->w / parent->size.x;

	frame = 0;

	if(frameDuration == 0.0) {
		Logger::Error("Frame duration not set or set to zero.");
	}

	renderer->AnimationRect = new SDL_Rect();

	renderer->AnimationRect->x = 0;
	renderer->AnimationRect->y = 0;
	renderer->AnimationRect->w = parent->size.x;
	renderer->AnimationRect->h = parent->size.y;
}

void BigNgine::AnimationBehaviour::Update(int deltaTime) {
	timer += deltaTime / 1000.0;

	if(timer >= frameDuration) {
		frame = (frame + 1) % frameCount;
		renderer->AnimationRect->x = frame * parent->size.x;
		timer -= frameDuration;
	}
}

void BigNgine::AnimationBehaviour::Destroy() {
	timer = 0;
	frame = 0;
}
