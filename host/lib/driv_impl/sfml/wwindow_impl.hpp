#ifndef LIB_DRIVERS_SFML_WWINDOW_IMPLEMENTATION_HPP
#define LIB_DRIVERS_SFML_WWINDOW_IMPLEMENTATION_HPP

#include <lib/drivers/window/wwindow.hpp>

namespace lib
{
	namespace drivers
	{
		namespace window
		{
			class SFMLWindow : public IWWindow
			{
				virtual bool create(u32 width, u32 height, u32 bpp, const char *title, u32 depth, u32 stencil, u32 antialiasing, u32  major, u32 minor, u32 attributes) override;
			};
		}
	}
}
#endif
