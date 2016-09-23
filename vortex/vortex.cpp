#include "include/vortex.hpp"
#include "include/iapplication.hpp"
#include "include/logger.hpp"

#include "common_def_priv.hpp"

#include <memory>

namespace vtx
{
	PRIVATE_STRUCT_DEFINITION(Vortex)
	{
		std::unique_ptr<IApplication> m_application;
	};

	void Vortex::setApplication(IApplication &&app)
	{
		m_private->m_application.reset(&app);
	}

	Vortex::Vortex() : m_private{ new PRIVATE_STRUCT_NAME(Vortex) }
	{
		Logger::createInstance();
		LDEBUG("Vortex library instance created");
	}

	Vortex::~Vortex()
	{
		LDEBUG("Vortex library instance beeing deleted");
		DELETE_PRIVATE_MPRIVATE_PIMPL(Vortex);
		LDEBUG("Vortex library instance deleted");
	}

	void Vortex::initialize()
	{
		LINFO("Initializing Vortex library...");
		if (!m_private->m_application) {
			LERROR("No application set");
			return;
		}
	}

	void Vortex::deinitialize()
	{
		LINFO("Deinitializing Vortex library...");
	}
}
