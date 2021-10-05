#include "cursor.h"

BigNgine::Vector2 Cursor::GetPosition() {
	double *x, *y;

	glfwGetCursorPos(Game::window, x, y);

	return BigNgine::Vector2((float)*x, (float)*y);
}

BigNgine::Vector2 SetPosition(BigNgine::Vector2 position) {
	glfwSetCursorPos(Game::window, position.x, position.y);
}

void Cursor::SetNormal() {
	glfwSetInputMode(Game::window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void Cursor::SetInvisible() {
	glfwSetInputMode(Game::window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
}

void Cursor::SetDisabled() {
	glfwSetInputMode(Game::window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}