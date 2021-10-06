#pragma once
#include "../../types/vector2/vector2.h"
#include "../game/game.h"
#include <GLFW/glfw3.h>

namespace Cursor {
	BigNgine::Vector2 GetPosition();
	void SetPosition(BigNgine::Vector2 position);

	void SetNormal();
	void SetInvisible();
	void SetDisabled();
}