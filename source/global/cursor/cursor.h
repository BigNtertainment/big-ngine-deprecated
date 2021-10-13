#pragma once
#include "../../types/vector2/vector2.h"
#include "../game/game.h"
#include <GLFW/glfw3.h>

namespace Cursor {
///	Get current position of cursor
///	@return BigNgine::Vector2 with position of cursor
	BigNgine::Vector2 GetPosition();
///	Sets position of cursor
/// @param position BigNgine::Vector2
	void SetPosition(const BigNgine::Vector2& position);
	
///	Sets cursor to normal
	void SetNormal();
/// Sets cursor to invisible
	void SetInvisible();
/// Disables cursor
	void SetDisabled();
}