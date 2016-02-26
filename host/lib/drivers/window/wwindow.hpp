#ifndef LIB_DRIVERS_WWINDOW_HPP
#define LIB_DRIVERS_WWINDOW_HPP

#include <lib/include/types.hpp>

namespace lib
{
	namespace drivers
	{
		namespace window
		{
			class IWWindow
			{
			public:
				virtual bool create(u32 width, u32 height, u32 bpp, const char *title, u32 depth, u32 stencil, u32 antialiasing, u32  major, u32 minor, u32 attributes) = 0;
			};
		}
	}
}

#endif
