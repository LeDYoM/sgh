#ifndef __LIB_COLOR_HPP__
#define __LIB_COLOR_HPP__

#include "types.hpp"

namespace lib
{
	namespace draw
	{
		class Color
		{
		public:
			Color();
			Color(u8 red, u8 green, u8 blue, u8 alpha = 255) :
				r{red}, g{green}, b{blue}, a{alpha} {}
			Color(u32 color) : 
				r{ u8{ (color & 0xff000000) >> 24 } },
				g{ static_cast<u8>((color & 0x00ff0000) >> 16) },
				b{ u8{ (color & 0x0000ff00) >> 8 } }, 
				a{ u8{ (color & 0x000000ff) >> 0 } } {}
			Color(const Color &rh) : r{ rh.r }, g{ rh.g }, b{ rh.b }, a{ rh.a } {}
			Color(Color &&rh) : r{ rh.r }, g{ rh.g }, b{ rh.b }, a{ rh.a } {}
			Color &operator=(const Color &rh) { r = rh.r; g = rh.g; b = rh.b; a = rh.a; }
			Color &operator=(const Color &&rh) { r = std::move(rh.r); g = std::move(rh.g); b = std::move(rh.b); a = std::move(rh.a); }
			u32 toInteger() const { return (r << 24) | (g << 16) | (b << 8) | a; }
			bool operator ==(const Color& rh) { return (r == rh.r && g == rh.g && b == rh.b && a == rh.a); }
			bool operator !=(const Color& rh) { return !(operator==(rh)); }
			Color operator +(const Color &rh) { return Color(u8(std::min(int(r) + rh.r, 255)), u8(std::min(int(g) + rh.g, 255)),
							 u8(std::min(int(b) + rh.b, 255)), u8(std::min(int(a) + rh.a, 255))); }

			Color operator -(const Color &rh) { return Color(u8(std::max(int(r) - rh.r, 0)), u8(std::max(int(g) - rh.g, 0)),
							 u8(std::max(int(b) - rh.b, 0)), u8(std::max(int(a) - rh.a, 0))); }

			Color operator *(const Color &rh) {
				return Color(u8(int(r) * rh.r / 255), u8(int(g) * rh.g / 255),
					u8(int(b) * rh.b / 255), u8(int(a) * rh.a / 255)); }

			Color &operator +=(const Color &rh) { r += rh.r; g += rh.g; b += rh.b; a += rh.a; return *this; }
			Color &operator -=(const Color &rh) { r -= rh.r; g -= rh.g; b -= rh.b; a -= rh.a; return *this; }

			Color& operator *=(const Color &rh) { r *= rh.r; g *= rh.g; b *= rh.b; a *= rh.a; return *this; }
			
			static const Color Black() { return Color{ 0, 0, 0 }; }
			static const Color White() { return Color{ 255, 255, 255 }; }
			static const Color Red() { return Color{ 255, 0, 0 }; }
			static const Color Green() { return Color{ 0, 255, 0 }; }
			static const Color Blue() { return Color{ 0, 0, 255 }; }
			static const Color Yellow() { return Color{ 255, 255, 0 }; }
			static const Color Magenta() { return Color{ 255, 0, 255 }; }
			static const Color Cyan() { return Color{ 0, 255, 255 }; }
			static const Color Transparent() { return Color{ 0, 0, 0, 0 }; }

		private:
			u8 r, g, b, a;
		};
	}
}
#endif
