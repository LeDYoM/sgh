#include "include/vortex.hpp"
#include "common_def_priv.hpp"

namespace vtx
{
	struct PRIVATE_STRUCT_NAME(Vortex)
	{
	};

	Vortex::Vortex() : m_private{new PRIVATE_STRUCT_NAME (Vortex)}
	{
	}

	Vortex::~Vortex()
	{
		DELETE_PRIVATE_MPRIVATE_PIMPL(Vortex)
	}

	void vtx::Vortex::initialize()
	{
	}

	void vtx::Vortex::deinitialize()
	{
	}
}
