#include "include/vortex.hpp"
#include "include/logger.hpp"
#include "include/vapplication.hpp"
#include "include/assert.hpp"

#include "memleakdetector.hpp"
#include "common_def_priv.hpp"

#include <memory>

namespace vtx
{
	PRIVATE_STRUCT_DEFINITION(Vortex)
	{
		std::unique_ptr<VApplication> m_application;
	};

	Vortex::Vortex() : m_private{ new PRIVATE_STRUCT_NAME(Vortex) }
	{
		installMemLeakDetector();
		Logger::createInstance();
		Logger::getInstance()->severity() = Logger::LogSeverity::Debug;
		LDEBUG("Vortex library instance created");
	}

	Vortex::~Vortex()
	{
		LDEBUG("Vortex library instance beeing deleted");
		DELETE_PRIVATE_MPRIVATE_PIMPL(Vortex);
		LDEBUG("Vortex library instance deleted");
		LDEBUG("Deleting logger and finishing...");
		Logger::destroyInstance();
	}

	bool Vortex::setApplication(VApplication &*app)
	{
		if (m_private->m_application)
		{
			LERROR("Error trying to reset an application. There is already one active application");
			return false;
		}

		m_private->m_application.reset(app);
		app = nullptr;
		return false;
	}

	void Vortex::initialize()
	{
		LINFO("Initializing Vortex library...");
		m_private->m_application->onStart();
	}

	void Vortex::deinitialize()
	{
		LINFO("Deinitializing Vortex library...");
	}

	int Vortex::execute()
	{
		SYSTEM_ASSERT(m_private->m_application != nullptr, "An application must be set to run");
		initialize();
		while (!update()) {

		}

		deinitialize();

		return 0;
	}

	int Vortex::update()
	{
		return 0;
	}

	bool Vortex_Init()
	{
		Vortex::createInstance();
		return Vortex::getConstInstance() != nullptr;
	}

	int Vortex_Loop()
	{
		return Vortex::getInstance()->execute();
	}

	bool Vortex_DeInit()
	{
		Vortex::destroyInstance();
		return Vortex::getConstInstance() == nullptr;
	}

}
