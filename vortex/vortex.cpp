#include "include/vortex.hpp"

#include "include/logger.hpp"
#include "include/vapplication.hpp"
#include "include/assert.hpp"
#include "include/types.hpp"

#include "include/videooptions.hpp"

#include "memleakdetector.hpp"
#include "common_def_priv.hpp"
#include "parameters.hpp"

#include <memory>

namespace vtx
{
	PRIVATE_STRUCT_DEFINITION(Vortex)
	{
		std::unique_ptr<VApplication> m_application;
		Parameters m_parameters;
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

	void Vortex::setCommandLineParameters(int argc, char * argv[])
	{
		m_private->m_parameters.resetParameters(argc, argv);
	}

	bool Vortex::setApplication(VApplication *app)
	{
		if (m_private->m_application)
		{
			LERROR("Error trying to reset an application. There is already one active application");
			return false;
		}

		m_private->m_application.reset(app);
		
		return true;
	}

	void Vortex::initialize()
	{
		LINFO("Initializing Vortex library...");
		m_private->m_application->onStart();

		VideoOptions::initialize();
	}

	void Vortex::deinitialize()
	{
		LINFO("Deinitializing Vortex library...");
	}

	int Vortex::execute()
	{
		SYSTEM_ASSERT(m_private->m_application, "An application must be set to run");
		initialize();

		LDEBUG("Entering execute loop");

		do 
		{
		} while (m_private->m_application->onUpdate());

		LDEBUG("Exiting execute loop");

		deinitialize();

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
