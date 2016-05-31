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
			LOG_CONSTRUCT("Driver fileName: " + fileName);
			fileName;
			return true;
		}

		sptr<drivers::window::IWWindow> Driver::newWindow()
		{
			__ASSERT(m_initialized, "Driver is not initialized");
			return sptr<drivers::window::SFMLWindow>(new drivers::window::SFMLWindow());
		}

		Driver::~Driver()
		{
			LOG_DESTRUCT_NOPARAMS;
		}

	}
}