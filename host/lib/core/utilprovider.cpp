#include "utilprovider.hpp"
#include "randomizer.hpp"
#include "log.hpp"

namespace lib
{
	UtilProvider::UtilProvider()
		: m_randomizer{ uptr<Randomizer>{new Randomizer()} } 
	{
		LOG_CONSTRUCT_NOPARAMS;
	}

	UtilProvider::~UtilProvider()
	{
		LOG_DESTRUCT_NOPARAMS;
	}

	u32 UtilProvider::getRandomNumer(u32 max /*= 1*/, u32 min /*= 0*/)
	{
		return m_randomizer->getUInt(max, min);
	}
}
