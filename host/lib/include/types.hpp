#ifndef __LIB_TYPES_HPP__
#define __LIB_TYPES_HPP__

#include <cstdint>
#include <memory>
#include <lib/core/compileconfig.hpp>
#include <SFML/System/Vector2.hpp>

namespace lib
{
	template <typename T>
	using sptr = std::shared_ptr<T>;

	template <typename T>
	using uptr = std::unique_ptr<T>;

	template <typename T>
	using wptr = std::weak_ptr<T>;

	using u64 = uint64_t;
	using s64 = int64_t;
	using u32 = uint32_t;
	using s32 = int32_t;
	using u16 = uint16_t;
	using s16 = int16_t;
	using u8 = uint8_t;
	using s8 = int8_t;
	using f32 = float;
	using f64 = double;

	// alias template
	template<class T>
	using vector2d = sf::Vector2<T>;

	using vector2du32 = vector2d<u32>;
	using vector2ds32 = vector2d<s32>;
	using vector2df = vector2d<f32>;
	using vector2du8 = vector2d<u8>;
	using vector2ds8 = vector2d<s8>;
}


#endif
