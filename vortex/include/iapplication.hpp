#ifndef VTX_IAPPLICATION_INCLUDE_HPP
#define VTX_IAPPLICATION_INCLUDE_HPP

#include "comp_config.hpp"

namespace vtx
{
	class VORTEX_API IApplication
	{
	public:
		constexpr IApplication() noexcept {}
		virtual ~IApplication() {}

		virtual void onStart() {}
		virtual void onFinish() {}

		virtual void onUpdate() {}
	};
}

#endif
