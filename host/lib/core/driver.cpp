#include "driver.hpp"
#include <lib/driv_impl/sfml/wwindow_impl.hpp>
#include "log.hpp"

namespace lib
{
	namespace core
	{

		bool Driver::initialize(const std::string &fileName)
		{
			LOG_CONSTRUCT("Driver fileName: " << fileName);
			fileName;
			return true;
		}

		sptr<drivers::window::IWWindow> Driver::newWindow()
		{
			return sptr<drivers::window::SFMLWindow>(new drivers::window::SFMLWindow());
		}

		Driver::~Driver()
		{
			LOG_DESTRUCT_NOPARAMS;
		}

	}
}