#ifndef VTX_COMMON_PATTERNS_HPP
#define VTX_COMMON_PATTERNS_HPP

#include "comp_config.hpp"

namespace vtx
{
	class VORTEX_API NoCopy
	{
	public:
		constexpr NoCopy() noexcept = default;
		virtual ~NoCopy() = default;

		NoCopy(const NoCopy &) = delete;
		NoCopy &operator=(const NoCopy&) = delete;
	};
}

#endif

