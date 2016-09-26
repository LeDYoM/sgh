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
		virtual void onStart() = 0;
		virtual void onFinish() = 0;

		virtual bool onUpdate() = 0;

		VApplication() {}
		virtual ~VApplication() {}

		DECLARE_PRIVATE_MPRIVATE_PIMPL(VApplication)
	};
}

#endif
