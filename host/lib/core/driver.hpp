#ifndef LIB_DRIVER_HPP
#define LIB_DRIVER_HPP

#include <lib/drivers/window/wwindow.hpp>
#include <string>

namespace lib
{
	namespace core
	{
		class Driver
		{
		public:
			bool initialize(const std::string &fileName);
			sptr<drivers::window::IWWindow> newWindow();
			virtual ~Driver();
		};
	}
}
#endif