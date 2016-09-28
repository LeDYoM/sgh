#ifndef VTX_SERIALIZABLE_INCLUDE_HPP
#define VTX_SERIALIZABLE_INCLUDE_HPP

#include "comp_config.hpp"
#include "types.hpp"
#include "str.hpp"

namespace vtx
{
	Str VORTEX_API &operator<<(Str &string, const u64);
	Str VORTEX_API &operator<<(Str &string, const s64);
	Str VORTEX_API &operator<<(Str &string, const f64);

}

#endif

