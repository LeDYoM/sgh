#ifndef VTX_VORTEX_MAIN_INCLUDE_HPP
#define VTX_VORTEX_MAIN_INCLUDE_HPP

#include "comp_config.hpp"
#include "common_def.hpp"

namespace vtx
{
	class VORTEX_API Vortex
	{
	public:
		Vortex();
		~Vortex();

		DECLARE_PRIVATE_MPRIVATE_PIMPL(Vortex)
	};
}

#endif
