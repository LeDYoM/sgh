#ifndef LIB_UTILPROVIDER_HPP
#define LIB_UTILPROVIDER_HPP

#include <lib/include/types.hpp>
#include <lib/core/appservice.hpp>

namespace lib
{
	class Randomizer;
	class UtilProvider : public AppService
	{
	public:
		UtilProvider();
		virtual ~UtilProvider();
		u32 getRandomNumer(u32 max = 1, u32 min = 0);
	private:
		uptr<Randomizer> m_randomizer;
	};
}
#endif
