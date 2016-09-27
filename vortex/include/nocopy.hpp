#ifndef VTX_NOCOPY_INCLUDE_HPP
#define VTX_NOCOPY_INCLUDE_HPP

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

