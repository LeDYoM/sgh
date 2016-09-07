#include "configuration.hpp"
#include <logger/include/logger.hpp>

namespace configuration
{
	DECLARE_MODULE_INFORMATION_BEGIN
	DECLARE_MODULE_INFORMATION_NAME("Configuration"),
	DECLARE_MODULE_INFORMATION_VERSION(0),
	DECLARE_MODULE_INFORMATION_SUBVERSION(1),
	DECLARE_MODULE_INFORMATION_PATCH(1)
	DECLARE_MODULE_INFORMATION_END
	DECLARE_MODULE_INFORMATION_GETTER(Configuration)

	using namespace std;

	Configuration::Configuration()
	{
	}

	Configuration::~Configuration()
	{
	}

	bool Configuration::start()
	{
		return true;
	}

	bool Configuration::stop()
	{
		return true;
	}
}

using namespace configuration;
DEFINE_MODULE_CREATION(Configuration);
