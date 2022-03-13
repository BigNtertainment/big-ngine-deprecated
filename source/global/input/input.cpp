#include "input.h"

bool Input::Get(int key) {
	return glfwGetKey(BigNgine::Game::GetInstance()->GetWindow(), key) == GLFW_PRESS;
}

Input::Callback::Callback(callbackfunc _callback) {
	callback = _callback;
}

void Input::Callback::Call(int key, int scancode, int mods) {
	callback(key, scancode, mods);
}