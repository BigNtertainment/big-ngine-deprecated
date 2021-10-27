#include "input.h"

bool Input::Get(int key) {
	return glfwGetKey(Game::window, key) == GLFW_PRESS;
}

Input::Callback::Callback(void(*_callback)(int, int, int)) {
	callback = _callback;
}

void Input::Callback::Call(int key, int scancode, int mods) {
	callback(key, scancode, mods);
}