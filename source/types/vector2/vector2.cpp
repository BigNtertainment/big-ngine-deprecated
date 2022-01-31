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

BigNgine::Vector2 BigNgine::operator+(BigNgine::Vector2 left, const BigNgine::Vector2& right) {
	BigNgine::Vector2 result;

	result.x = left.x + right.x;
	result.y = left.y + right.y;

	return result;
}

BigNgine::Vector2 BigNgine::operator-(BigNgine::Vector2 left, const BigNgine::Vector2& right) {
	BigNgine::Vector2 result;

	result.x = left.x - right.x;
	result.y = left.y - right.y;

	return result;
}

BigNgine::Vector2 BigNgine::operator*(BigNgine::Vector2 left, const BigNgine::Vector2& right) {
	BigNgine::Vector2 result;

	result.x = left.x * right.x;
	result.y = left.y * right.y;

	return result;
}

BigNgine::Vector2 BigNgine::operator/(BigNgine::Vector2 left, const BigNgine::Vector2& right) {
	BigNgine::Vector2 result;

	result.x = left.x * right.x;
	result.y = left.y * right.y;

	return result;
}

BigNgine::Vector2 BigNgine::operator*(BigNgine::Vector2 left, const int& right) {
	BigNgine::Vector2 result;

	result.x = left.x * right;
	result.y = left.y * right;

	return result;
}

BigNgine::Vector2 BigNgine::operator/(BigNgine::Vector2 left, const int& right) {
	BigNgine::Vector2 result;

	result.x = left.x / right;
	result.y = left.y / right;

	return result;
}

std::ostream& BigNgine::operator<< (std::ostream& stream, const BigNgine::Vector2& vector) {
	std::stringstream ss;

	ss << "(" << vector.x << ", " << vector.y << ")";

	return stream << ss.str();
}