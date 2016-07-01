#ifndef LIB_VECTOR2D_HPP
#define LIB_VECTOR2D_HPP

namespace lib
{
	template <typename T>
	class vector2d
	{
	public:

		vector2d() : x{}, y{} {}
		vector2d(T X, T Y) : x{ X }, y{ Y } {}
		vector2d(const vector2d<T> &) = default;
		vector2d(vector2d &&v) : x{ std::move(v.x) }, y{ std::move(v.y) } {}
		vector2d &operator=(const vector2d<T> &) = default;
		vector2d &operator=(vector2d<T> &&v) { x = std::move(v.x); y = std::move(v.y); return *this; }

		template <typename U>
		explicit vector2d(const vector2d<U>& vector) : x{ static_cast<T>(vector.x) }, y{ static_cast<T>(vector.y) } {}

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
		inline bool operator !=(const vector2d &right) const {	return !(*this == right); }

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
