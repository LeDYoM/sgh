#ifndef VTX_VORTEX_MAIN_INCLUDE_HPP
#define VTX_VORTEX_MAIN_INCLUDE_HPP

#include "comp_config.hpp"
#include "common_def.hpp"
#include "singleton.hpp"

namespace vtx
{
	class Application;
	class VORTEX_API Vortex : public Singleton<Vortex>
	{
	public:
		void initialize();
		void deinitialize();

		void setApplication(Application &&app);
	private:
		Vortex();
		~Vortex();
		friend class Singleton<Vortex>;
		DECLARE_PRIVATE_MPRIVATE_PIMPL(Vortex)
	};
}

#endif
