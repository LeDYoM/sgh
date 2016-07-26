#include "driver.hpp"
#include <lib/driv_impl/sfml/wwindow_impl.hpp>
#include "log.hpp"

namespace lib
{
	namespace core
	{

		Driver::Driver()
		{
			LOG_CONSTRUCT_NOPARAMS;
		}

		bool Driver::initialize(const std::string &fileName)
		{
			LOG_DEBUG("Initializing driver");
			LOG_DEBUG("Driver fileName: " + fileName);
			fileName;
			m_initialized = true;
			return true;
		}

		sptr<drivers::window::IWWindow> Driver::currentWindow()
		{
			__ASSERT(m_window, "There is no window created");
			return m_window;
		}

		sptr<drivers::window::IWWindow> Driver::newWindow(const WindowCreationParams & wcp)
		{
			__ASSERT(m_initialized, "Driver is not initialized");
			__ASSERT(!m_window, "Window is already created");
			m_window = sptr<drivers::window::SFMLWindow>(new drivers::window::SFMLWindow());
			return currentWindow();
		}

		Driver::~Driver()
		{
			m_initialized = false;
			LOG_DESTRUCT_NOPARAMS;
		}

	}
}