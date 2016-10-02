#ifndef VTX_ASSERT_INCLUDE_HPP
#define VTX_ASSERT_INCLUDE_HPP

#include "comp_config.hpp"
#include "singleton.hpp"
#include "logger.hpp"

#include <stdexcept>

namespace vtx
{
	class VORTEX_API Assert : public Singleton<Assert>
	{
	public:
		Assert();
		~Assert();

		DECLARE_PRIVATE_MPRIVATE_PIMPL(Assert)
	};
}

#ifdef USE_NATIVE_ASSERT
	#include <cassert>
	#define SYSTEM_ASSERT(x,p)	if (!(x)) LERROR(p); assert(x);
#else
	#define SYSTEM_ASSERT(x,p)	if (!(x)) LERROR(p);
#endif

#endif
