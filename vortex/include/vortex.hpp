#ifndef VTX_VORTEX_MAIN_INCLUDE_HPP
#define VTX_VORTEX_MAIN_INCLUDE_HPP

#include "comp_config.hpp"
#include "common_def.hpp"
#include "singleton.hpp"

namespace vtx
{
	class VORTEX_API Vortex : public Singleton<Vortex>
	{
	public:
		Vortex();
		~Vortex();

		void initialize();
		void deinitialize();

		DECLARE_PRIVATE_MPRIVATE_PIMPL(Vortex)
	};
}

#endif
