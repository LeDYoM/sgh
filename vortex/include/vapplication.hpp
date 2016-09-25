#ifndef VTX_VORTEX_MAIN_INCLUDE_HPP
#define VTX_VORTEX_MAIN_INCLUDE_HPP

#include "comp_config.hpp"
#include "common_def.hpp"
#include "singleton.hpp"

namespace vtx
{
	class VORTEX_API VApplication : public Singleton<VApplication>
	{
	public:
		virtual void initialize();
		virtual void deinitialize();

		int execute();
	protected:
		VApplication();
		~VApplication();

		int update();

		friend class Singleton<VApplication>;
		DECLARE_PRIVATE_MPRIVATE_PIMPL(VApplication)
	};
}

#endif
