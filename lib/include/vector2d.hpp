#ifndef LIB_VECTOR2D_HPP
#define LIB_VECTOR2D_HPP

#include <lib/core/data.hpp>

namespace lib
{
	template <typename T>
	class LIB_API vector2d
	{
	public:

		inline explicit vector2d() : x{}, y{} {};
		inline vector2d(T X, T Y) : x{ X }, y{ Y } {}
		inline vector2d(const vector2d<T> &) = default;
		inline vector2d &operator=(const vector2d<T> &) = default;

		template <typename U>
		inline explicit vector2d(const vector2d<U>& vector) : x{ static_cast<T>(vector.x) }, y{ static_cast<T>(vector.y) } {}

		inline vector2d &operator+=(const vector2d &right)
		{ 
			x += right.x;
			y += right.y;
			return *this;
		}

		inline vector2d &operator-=(const vector2d &right)
		{
			x -= right.x;
			y -= right.y;
			return *this;
		}

		inline vector2d &operator*=(const vector2d &right)
		{
			x *= right.x;
			y *= right.y;
			return *this;
		}

		inline vector2d &operator*=(const T &scalar)
		{
			x *= scalar;
			y *= scalar;
			return *this;
		}

		inline vector2d &operator/=(const vector2d &right)
		{
			x /= right.x;
			y /= right.y;
			return *this;
		}

		inline vector2d &operator/=(const T &scalar)
		{
			x /= scalar;
			y /= scalar;
			return *this;
		}

		inline vector2d &operator-()
		{
			x = -x;
			y = -y;
			return *this;
		}

		inline vector2d operator+(const vector2d &right) const { return (vector2d(*this) += right); }
		inline vector2d operator-(const vector2d &right) const { return (vector2d(*this) -= right); }
		inline vector2d operator*(const vector2d &right) const { return (vector2d(*this) *= right); }
		inline vector2d operator/(const vector2d &right) const { return (vector2d(*this) /= right); }
		inline vector2d operator*(const T &right) const { return (vector2d(*this) *= right);	}
		inline vector2d operator/(const T &right) const { return (vector2d(*this) /= right); }
		inline bool operator ==(const vector2d &right) const { return (x == right.x && y == right.y); }
		inline bool operator !=(const vector2d &right) const {	return !(*operator==(right)); }

		T x;
		T y;
	};

	using vector2du32 = vector2d<u32>;
	using vector2ds32 = vector2d<s32>;
	using vector2df = vector2d<f32>;
	using vector2du8 = vector2d<u8>;
	using vector2ds8 = vector2d<s8>;

}

#endif
