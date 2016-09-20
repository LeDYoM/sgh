#include "include/vortex.hpp"
#include "include/app.hpp"

#include "common_def_priv.hpp"

#include <memory>

namespace vtx
{
	struct PRIVATE_STRUCT_NAME(Vortex)
	{
		std::unique_ptr<Application> m_application;
	};

	void Vortex::setApplication(Application &&app)
	{
		m_private->m_application.reset(&app);
	}

	Vortex::Vortex() : m_private{ new PRIVATE_STRUCT_NAME(Vortex) }
	{
	}

	Vortex::~Vortex()
	{
		DELETE_PRIVATE_MPRIVATE_PIMPL(Vortex)
	}

	void Vortex::initialize()
	{
	}

	void Vortex::deinitialize()
	{
	}
}
