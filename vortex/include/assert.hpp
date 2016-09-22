#ifndef VTX_ASSERT_INCLUDE_HPP
#define VTX_ASSERT_INCLUDE_HPP

#include "comp_config.hpp"
#include "singleton.hpp"

namespace vtx
{
	class VORTEX_API Assert : public Singleton<Assert>
	{
	public:
		Assert();
		~Assert();
	};
}

#endif
