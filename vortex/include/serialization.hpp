#ifndef VTX_SERIALIZABLE_INCLUDE_HPP
#define VTX_SERIALIZABLE_INCLUDE_HPP

#include "comp_config.hpp"
#include "types.hpp"
#include "str.hpp"

namespace vtx
{
	class VORTEX_API SerializationBuffer
	{
		SerializationBuffer&operator<<(const u64);
		SerializationBuffer&operator<<(const s64);
		SerializationBuffer&operator<<(const u32);
		SerializationBuffer&operator<<(const s32);
		SerializationBuffer&operator<<(const u16);
		SerializationBuffer&operator<<(const s16);
		SerializationBuffer&operator<<(const u8);
		SerializationBuffer&operator<<(const s8);
		SerializationBuffer&operator<<(const f64);
		SerializationBuffer&operator<<(const f32);
	};

}

#endif

