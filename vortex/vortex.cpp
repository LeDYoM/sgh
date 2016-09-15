#include "include/vortex.hpp"

namespace vtx
{
	struct Vortex::VortexPrivate
	{
		int a;
	};

	Vortex::Vortex()
		: m_private{new VortexPrivate}
	{
	}

	Vortex::~Vortex()
	{
		delete m_private;
	}
}
