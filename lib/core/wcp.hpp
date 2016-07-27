#ifndef LIB_WINDOWCREATIONPARAMS_HPP
#define LIB_WINDOWCREATIONPARAMS_HPP

#include <lib/include/types.hpp>

namespace lib
{
	struct WindowCreationParams
	{
		vector2du32 size{ 1024,768 };
		u32 bpp{ 16 };
		u32 antialiasing{ 0 };
		bool vsync{ false };
		bool fullScreen{ false };
		bool resizable{ false };
		bool titleBar{ true };
		str windowTitle;
	};
}

#endif
