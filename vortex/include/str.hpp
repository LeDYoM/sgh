#ifndef VTX_STRING_INCLUDE_HPP
#define VTX_STRING_INCLUDE_HPP

#include "comp_config.hpp"
#include "common_def.hpp"

namespace vtx
{
	class VORTEX_API Str
	{
	public:
		Str() noexcept;
		Str(const char *) noexcept;
		Str(const Str&) noexcept;
		Str &operator=(const Str&) noexcept;
		constexpr Str(Str&&) noexcept;
		Str &operator=(Str&&) noexcept;

		const char *c_str() const noexcept;

		~Str();

		DECLARE_PRIVATE_MPRIVATE_PIMPL(Str)
	};
}

#endif

