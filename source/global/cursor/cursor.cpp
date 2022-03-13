#include "cursor.h"

BigNgine::Vector2 Cursor::GetPosition() {
	double x = 0, y = 0;

	glfwGetCursorPos(BigNgine::Game::GetInstance()->GetWindow(), &x, &y);

	return BigNgine::Vector2(x, y);
}

void Cursor::SetPosition(const BigNgine::Vector2& position) {
	glfwSetCursorPos(BigNgine::Game::GetInstance()->GetWindow(), position.x, position.y);
}

void Cursor::SetNormal() {
	glfwSetInputMode(BigNgine::Game::GetInstance()->GetWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void Cursor::SetInvisible() {
	glfwSetInputMode(BigNgine::Game::GetInstance()->GetWindow(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
}

void Cursor::SetDisabled() {
	glfwSetInputMode(BigNgine::Game::GetInstance()->GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}