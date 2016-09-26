#include "include/vortex.hpp"
#include "include/iapplication.hpp"
#include "include/logger.hpp"

#include "common_def_priv.hpp"

#include <memory>

namespace vtx
{
	PRIVATE_STRUCT_DEFINITION(Vortex)
	{
	};

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
	}

	void Vortex::deinitialize()
	{
		LINFO("Deinitializing Vortex library...");
	}

	int Vortex::execute()
	{
		while (!update()) {

		}

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

	bool Vortex_DeInit()
	{
		Vortex::destroyInstance();
		return Vortex::getConstInstance() == nullptr;
	}

}
