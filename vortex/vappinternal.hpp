#ifndef VTX_VORTEX_APPLICATION_INTERNAL_HPP
#define VTX_VORTEX_APPLICATION_INTERNAL_HPP

#include "include/comp_config.hpp"
#include "include/common_def.hpp"
#include "include/singleton.hpp"

namespace vtx
{
	namespace intern
	{
		class VApplicationInternal final : public Singleton<VApplicationInternal>
		{
		public:
			inline static VApplicationInternal*const createInstance() { return Singleton<VApplicationInternal>::createInstance(); }
			inline static void destroyInstance() { return Singleton<VApplicationInternal>::destroyInstance(); }

			void initialize();
			void deinitialize();

			int execute();
		protected:
			VApplicationInternal();
			~VApplicationInternal();

			int update();

			friend class Singleton<VApplicationInternal>;
			DECLARE_PRIVATE_MPRIVATE_PIMPL(VApplicationInternal)
		};
	}
}

#endif
