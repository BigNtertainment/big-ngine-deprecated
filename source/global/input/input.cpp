#include "input.h"

bool Input::Get(int key) {
	return glfwGetKey(Game::window, key) == GLFW_PRESS;
}

std::vector<Input::Callback*> callbacks;

int AutoIncrement = 0;

Input::Callback::Callback(void(*_callback)(int, int, int)) {
	callback = _callback;
	ID = AutoIncrement;
	AutoIncrement++;

	callbacks.push_back(this);
}

Input::Callback::~Callback() {
	const int searchID = ID;

	// https://stackoverflow.com/questions/7958216/c-remove-if-on-a-vector-of-objects
	callbacks.erase(
		std::remove_if(
			callbacks.begin(),
			callbacks.end(),
			[searchID](Callback* callback) { return callback->ID == searchID; }
		),
		callbacks.end()
	);
}

void Input::Callback::ExecuteCallbacks(GLFWwindow* window, int key, int scancode, int action, int mods) {
	for(Callback* callback : callbacks) {
		if(callback->active && callback->event == action)
			callback->callback(key, scancode, mods);
	}
}