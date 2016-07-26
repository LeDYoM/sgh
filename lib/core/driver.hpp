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
			explicit Driver();
			bool initialize(const std::string &fileName);
			sptr<drivers::window::IWWindow> currentWindow();
			sptr<drivers::window::IWWindow> newWindow(const WindowCreationParams &wcp);
			virtual ~Driver();
		private:
			bool m_initialized{ false };
			sptr<drivers::window::IWWindow> m_window;
		};
	}
}
#endif
