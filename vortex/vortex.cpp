#include "include/vortex.hpp"

namespace vtx
{
	struct Vortex::VortexPrivate
	{
		int a;
	};

	Vortex::Vortex() : m_private{new VortexPrivate}
	{
	}

	Vortex::~Vortex()
	{
		if (m_private) {
			delete m_private;
			m_private = nullptr;
		}
	}
}
