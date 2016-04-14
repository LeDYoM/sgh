#ifndef LIB_WINDOWCREATIONPARAMS_HPP
#define LIB_WINDOWCREATIONPARAMS_HPP

#include <string>
#include "types.hpp"

namespace lib
{
	struct WindowCreationParams
	{
		std::string windowTitle;
		u32 width{ 1024 };
		u32 height{ 768 };
		u32 bpp{ 16 };
		u32 antialiasing{ 0 };
		bool vsync{ false };
		bool fullScreen{ false };
		bool resizable{ false };
		inline WindowCreationParams(const std::string &wt, const u32 w, const u32 h, const u32 b, const u32 aa, const bool vs, const bool fs, const bool rs)
			: windowTitle(wt), width{ w }, height{ h }, bpp{ b }, antialiasing{ aa }, vsync{ vs }, fullScreen{ fs }, resizable{ rs } {}
	};
}

#endif
