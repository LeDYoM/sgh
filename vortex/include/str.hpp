#ifndef VTX_STRING_INCLUDE_HPP
#define VTX_STRING_INCLUDE_HPP

#include "comp_config.hpp"
#include "common_def.hpp"

namespace vtx
{
	class VORTEX_API Str
	{
	public:
		Str();
		Str(const char *);
		Str(const Str&);
		Str &operator=(const Str&);
		constexpr Str(Str&&);
		Str &operator=(Str&&);

		~Str();

		DECLARE_PRIVATE_MPRIVATE_PIMPL(Str)
	};
}

#endif

