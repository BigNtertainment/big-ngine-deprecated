#pragma once

namespace BigNgine {
	class Vector2 {
	public:
		Vector2();
		Vector2(float _x, float _y);
		Vector2(const Vector2& other);

		float x, y;
	};
}