#pragma once
#include <sstream>
#include "../vector2/vector2.h"

namespace BigNgine {
	template<typename Num, typename = typename std::enable_if<std::is_arithmetic<Num>::value>>
	class BasicVector3 {
	public:
		Num x, y, z;

		constexpr BasicVector3(): x(0), y(0), z(0) {};
		constexpr BasicVector3(Num _x, Num _y, Num _z): x(_x), y(_y), z(_z) {};
        constexpr explicit BasicVector3(const Vector2 &v2): x(v2.x), y(v2.y), z(0) {};
		constexpr BasicVector3(const BasicVector3& other): x(other.x), y(other.y), z(other.z) {};

		constexpr auto operator+(const BasicVector3& right) const {
			return BasicVector3(x + right.x, y + right.y, z + right.z);
		}

		constexpr auto operator-(const BasicVector3& right) const {
			return BasicVector3(x - right.x, y - right.y, z - right.z);
		}

		constexpr auto operator*(const BasicVector3& right) const {
			return BasicVector3(x * right.x, y * right.y, z * right.z);
		}

		constexpr auto operator/(const BasicVector3& right) const {
			return BasicVector3(x / right.x, y / right.y, z / right.z);
		}

		constexpr auto operator*(Num right) const {
			return BasicVector3(x * right, y * right, z * right);
		}

		constexpr auto operator/(Num right) const {
			return BasicVector3(x / right, y / right, z / right);
		}

		friend auto& operator<< (std::ostream& stream, const BasicVector3<Num>& vector) {
			return stream << "(" << vector.x << ", " << vector.y << ", " << vector.z << ")";
		}
	};

	using Vector3 = BasicVector3<float>;
	using VectorD3 = BasicVector3<double>;
}