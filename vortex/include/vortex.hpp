#ifndef VTX_VORTEX_MAIN_INCLUDE_HPP
#define VTX_VORTEX_MAIN_INCLUDE_HPP

#include "comp_config.hpp"

namespace vtx
{
	class VORTEX_API Vortex
	{
	public:
		Vortex();
		~Vortex();
	private:
		struct VortexPrivate;
		VortexPrivate *m_private;
	};
}

#endif
