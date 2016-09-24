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
		Logger::createInstance();
		LDEBUG("Vortex library instance created");
	}

	VApplication::~VApplication()
	{
		LDEBUG("Vortex library instance beeing deleted");
		DELETE_PRIVATE_MPRIVATE_PIMPL(VApplication);
		LDEBUG("Vortex library instance deleted");
	}

	void VApplication::initialize()
	{
		LINFO("Initializing Vortex library...");
	}

	void VApplication::deinitialize()
	{
		LINFO("Deinitializing Vortex library...");
	}

	int VApplication::execute()
	{
		while (!update()) {

		}

		return 0;
	}

	int VApplication::update()
	{
		return 0;
	}
}
