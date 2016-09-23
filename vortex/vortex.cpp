#include "include/vortex.hpp"
#include "include/iapplication.hpp"
#include "include/logger.hpp"

#include "common_def_priv.hpp"

#include <memory>

namespace vtx
{
	struct PRIVATE_STRUCT_NAME(Vortex)
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
		ldebug() << "Vortex library instance created" << endline();
	}

	Vortex::~Vortex()
	{
		LDEBUG("Vortex library instance beeing deleted");
		DELETE_PRIVATE_MPRIVATE_PIMPL(Vortex);
		ldebug() << "Vortex library instance deleted" << endline();
	}

	void Vortex::initialize()
	{
		linfo() << "Initializing Vortex library..." << endline();
		if (!m_private->m_application) {
			lerror() << "No application set" << endline();
			return;
		}
	}

	void Vortex::deinitialize()
	{
		linfo() << "Deinitializing Vortex library..." << endline();
	}
}
