#include "vappinternal.hpp"
#include "include/iapplication.hpp"
#include "include/logger.hpp"

#include "common_def_priv.hpp"

#include <memory>

namespace vtx
{
	namespace intern
	{
		PRIVATE_STRUCT_DEFINITION(VApplicationInternal)
		{
		};

		VApplicationInternal::VApplicationInternal() : m_private{ new PRIVATE_STRUCT_NAME(VApplicationInternal) }
		{
			Logger::createInstance();
			LDEBUG("Vortex library instance created");
		}

		VApplicationInternal::~VApplicationInternal()
		{
			LDEBUG("Vortex library instance beeing deleted");
			DELETE_PRIVATE_MPRIVATE_PIMPL(VApplicationInternal);
			LDEBUG("Vortex library instance deleted");
		}

		void VApplicationInternal::initialize()
		{
			LINFO("Initializing Vortex library...");
		}

		void VApplicationInternal::deinitialize()
		{
			LINFO("Deinitializing Vortex library...");
		}

		int VApplicationInternal::execute()
		{
			while (!update()) {

			}

			return 0;
		}

		int VApplicationInternal::update()
		{
			return 0;
		}
	}
}
