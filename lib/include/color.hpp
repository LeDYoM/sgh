#ifndef LIB_COLOR_HPP
#define LIB_COLOR_HPP

#include "types.hpp"
#include <algorithm>

namespace lib
{
	namespace draw
	{
		class Color
		{
		public:
			Color() : r{ 0 }, g{ 0 }, b{ 0 }, a{ 255 } {}
			Color(u8 red, u8 green, u8 blue, u8 alpha = 255)
				: r{ red }, g{ green }, b{ blue }, a{ alpha } {}

			explicit Color(u32 color)
				: r{ static_cast<u8>((color & 0xff000000) >> 24) },
				g{ static_cast<u8>((color & 0x00ff0000) >> 16) },
				b{ static_cast<u8>((color & 0x0000ff00) >> 8) },
				a{ static_cast<u8>((color & 0x000000ff) >> 0) } {}

			u32 toInteger() const { return (r << 24) | (g << 16) | (b << 8) | a; }
			Color(const Color&) = default;

			bool operator ==(const Color& right) const
			{
				return (r == right.r && g == right.g && b == right.b && a == right.a);
			}

			bool operator !=(const Color& right) const
			{
				return !(*this == right);
			}

			Color operator+(const Color& right) const
			{
				return (Color(*this) += right);
			}

			Color operator -(const Color& right) const
			{
				return (Color(*this) -= right);
			}

			Color operator*(const Color& right) const
			{
				return (Color(*this) *= right);
			}

			Color &operator +=(const Color& right)
			{
				r = static_cast<u8>(std::min(static_cast<u32>(r)+right.r, 255u));
				g = static_cast<u8>(std::min(static_cast<u32>(g)+right.g, 255u));
				b = static_cast<u8>(std::min(static_cast<u32>(b)+right.b, 255u));
				a = static_cast<u8>(std::min(static_cast<u32>(a)+right.a, 255u));
				return *this;
			}

			Color &operator -=(const Color& right)
			{
				r = static_cast<u8>(std::max(static_cast<u32>(r) - right.r, 0u));
				g = static_cast<u8>(std::max(static_cast<u32>(g) - right.g, 0u));
				b = static_cast<u8>(std::max(static_cast<u32>(b) - right.b, 0u));
				a = static_cast<u8>(std::max(static_cast<u32>(a) - right.a, 0u));
				return *this;

			}

			Color &operator *=(const Color& right)
			{
				r = static_cast<u8>(static_cast<u32>(r)* right.r / 255);
				g = static_cast<u8>(static_cast<u32>(g)* right.g / 255);
				b = static_cast<u8>(static_cast<u32>(b)* right.b / 255);
				a =	static_cast<u8>(static_cast<u32>(a)* right.a / 255);
				return *this;
			}

			Color operator*(const f32 delta) const
			{
				return Color(
					static_cast<u8>(static_cast<u32>(r)* delta),
					static_cast<u8>(static_cast<u32>(g)* delta),
					static_cast<u8>(static_cast<u32>(b)* delta),
					static_cast<u8>(static_cast<u32>(a)* delta)
					);
			}

			static const Color Black() { return Color{ 0, 0, 0 }; }
			static const Color White() { return Color{ 255, 255, 255 }; }
			static const Color Red() { return Color{ 255, 0, 0 }; }
			static const Color Green() { return Color{ 0, 255, 0 }; }
			static const Color Blue() { return Color{ 0, 0, 255 }; }
			static const Color Yellow() { return Color{ 255, 255, 0 }; }
			static const Color Magenta() { return Color{ 255, 0, 255 }; }
			static const Color Cyan() { return Color{ 0, 255, 255 }; }
			static const Color Transparent() { return Color{ 0, 0, 0, 0 }; }

			u8 r;
			u8 g;
			u8 b;
			u8 a;
		};
	}
}

#endif
