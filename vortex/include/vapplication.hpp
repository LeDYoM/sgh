#ifndef VTX_VORTEX_MAIN_INCLUDE_HPP
#define VTX_VORTEX_MAIN_INCLUDE_HPP

#include "comp_config.hpp"
#include "common_def.hpp"
#include "singleton.hpp"

namespace vtx
{
	class VORTEX_API VApplication
	{
	public:

		int execute();
	protected:
		VApplication();
		~VApplication();

		int update();

		DECLARE_PRIVATE_MPRIVATE_PIMPL(VApplication)
	};
}

#endif
