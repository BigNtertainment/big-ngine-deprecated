#include "cursor.h"

//FIXME: this crashes program again...
BigNgine::Vector2 Cursor::GetPosition() {
	double *x = nullptr, *y = nullptr;

	glfwGetCursorPos(Game::window, x, y);

	return {(float)*x, (float)*y};
}

void Cursor::SetPosition(const BigNgine::Vector2& position) {
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