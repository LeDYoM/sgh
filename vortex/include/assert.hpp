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

#define USE_NATIVE_ASSERT

#ifdef USE_NATIVE_ASSERT
	#include <cassert>
	#define SYSTEM_ASSERT(x)	assert(x)
#else
	#define SYSTEM_ASSERT(x,p)	if (!(x)) lerror() << p << endline();
#endif

#endif
