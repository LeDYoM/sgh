#ifndef __LIB_TYPES_HPP__
#define __LIB_TYPES_HPP__

#include "compconfig.hpp"
#include <cstdint>
#include <memory>
#include <map>
#include <string>
#include <vector>
#include <list>

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

	template <typename T>
	using Vector = std::vector<T>;

//	template <typename T>
//	using List = std::list<T>;

//	LIB_API std::string;
	using str = std::string;

	EXPIMP_TEMPLATE template class LIB_API std::basic_string<char, std::char_traits<char>, std::allocator<char> >;

	EXPIMP_TEMPLATE template class LIB_API std::map<str, str>;
	using StringMap = std::map<str, str>;
}

#include "vector2d.hpp"
#include "rect.hpp"

#endif
