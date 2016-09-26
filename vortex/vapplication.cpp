#include "include/vapplication.hpp"
#include "include/iapplication.hpp"
#include "include/logger.hpp"

#include "common_def_priv.hpp"

#include <memory>

namespace vtx
{
	PRIVATE_STRUCT_DEFINITION(VApplication)
	{
	};

	VApplication::VApplication() : m_private{ new PRIVATE_STRUCT_NAME(VApplication) }
	{
		LDEBUG("Vortex application instance created");
	}

	VApplication::~VApplication()
	{
		LDEBUG("Vortex library instance beeing deleted");
		DELETE_PRIVATE_MPRIVATE_PIMPL(VApplication);
		LDEBUG("Vortex library instance deleted");
	}

	int VApplication::execute()
	{
//		while (!update()) {

//		}

		return 0;
	}

	int VApplication::update()
	{
		return 0;
	}
}
