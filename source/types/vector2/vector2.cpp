#include "vector2.h"

BigNgine::Vector2::Vector2() {
	x = 0.0;
	y = 0.0;
}

BigNgine::Vector2::Vector2(float _x, float _y) {
	x = _x;
	y = _y;
}

BigNgine::Vector2::Vector2(const Vector2& other) {
	x = other.x;
	y = other.y;
}