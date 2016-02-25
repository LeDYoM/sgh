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

		vector2d operator-() { return vector2d{-x,-y} }
		vector2d &operator+=(const vector2d &right)
		{ 
			x += right.x;
			y += right.y;
			return *this;
		}

		vector2d &operator-=(const vector2d &right)
		{
			x -= right.x;
			y -= right.y;
			return *this;
		}

		vector2d &operator*=(const vector2d &right)
		{
			x *= right.x;
			y *= right.y;
			return *this;
		}

		vector2d &operator/=(const vector2d &right)
		{
			x /= right.x;
			y /= right.y;
			return *this;
		}

		vector2d &operator*=(const T &right)
		{
			x *= right;
			y *= right;
			return *this;
		}

		vector2d &operator/=(const T &right)
		{
			x /= right;
			y /= right;
			return *this;
		}

		vector2d operator+(const vector2d &right) const
		{
			return (vector2d{ *this } += right);
		}

		vector2d operator-(const vector2d &right) const
		{
			return (vector2d{ *this } -= right);
		}

		vector2d operator*(const vector2d &right) const
		{
			return (vector2d{ *this } *= right);
		}
		vector2d operator/(const vector2d &right) const
		{
			return (vector2d{ *this } /= right);
		}

		vector2d operator*(const T &right) const
		{
			return (vector2d{ *this } *= right);
		}

		vector2d operator/(const T &right) const
		{
			return (vector2d{ *this } /= right);
		}

		bool operator ==(const vector2d &right) const
		{
			return (x == right.x && y == right.y);
		}

		bool operator !=(const vector2d &right) const
		{
			return !(*this == right);
		}

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
