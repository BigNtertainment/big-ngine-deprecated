#include "behaviour.h"
#include <algorithm>

BigNgine::Behaviour::Behaviour() {

}

BigNgine::Behaviour::~Behaviour() {
	parent->behaviours.erase(std::remove(parent->behaviours.begin(), parent->behaviours.end(), this), parent->behaviours.end());
}
