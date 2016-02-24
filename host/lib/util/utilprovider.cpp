#include "utilprovider.hpp"
#include "randomizer.hpp"
#include <lib/core/log.hpp>

namespace lib
{
	namespace util
	{

		UtilProvider::UtilProvider(core::AppController *appController)
			: AppService{ appController }, m_randomizer{ uptr<Randomizer>{new Randomizer()} } 
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
}
