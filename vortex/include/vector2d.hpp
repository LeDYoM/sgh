#ifndef LIB_VECTOR2D_HPP
#define LIB_VECTOR2D_HPP

#include "types.hpp"

namespace vtx
{
	template <typename T>
	class VORTEX_API vector2d
	{
	public:
		inline constexpr explicit vector2d() noexcept = default;
		inline constexpr vector2d(T X, T Y) noexcept : x{ X }, y{ Y } {}
		inline constexpr vector2d(const vector2d<T> &) noexcept = default;

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
	using vector2du16 = vector2d<u16>;
	using vector2ds16 = vector2d<s16>;
	using vector2df = vector2d<f32>;
	using vector2du8 = vector2d<u8>;
	using vector2ds8 = vector2d<s8>;

	class VORTEX_API SerializableVector2d : public vector2ds32, public ISerializable
	{
		virtual SerializationObject &serialize(SerializationObject &so) override {
			so << x;
			so << y;
			return so; 
		};
		virtual SerializationObject &deserialize(SerializationObject&so) override { return so; }
	};

}

#endif
