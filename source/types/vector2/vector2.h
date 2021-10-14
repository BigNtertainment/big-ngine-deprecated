#pragma once

namespace BigNgine {
	class Vector2 {
	public:
		float x, y;

		Vector2();
		explicit Vector2(float _x);
		Vector2(float _x, float _y);
		Vector2(const Vector2& other);
	};

	Vector2 operator+(Vector2 left, const Vector2& right);
	Vector2 operator-(Vector2 left, const Vector2& right);
	Vector2 operator*(Vector2 left, const Vector2& right);
	Vector2 operator/(Vector2 left, const Vector2& right);
	Vector2 operator*(Vector2 left, const int& right);
	Vector2 operator/(Vector2 left, const int& right);
}