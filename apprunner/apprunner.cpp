#include "apprunner.hpp"
#include <logger/include/logger.hpp>

namespace apprunner
{
	DECLARE_MODULE_INFORMATION_BEGIN
	DECLARE_MODULE_INFORMATION_NAME("AppRunner"),
	DECLARE_MODULE_INFORMATION_VERSION(0),
	DECLARE_MODULE_INFORMATION_SUBVERSION(1),
	DECLARE_MODULE_INFORMATION_PATCH(4)
	DECLARE_MODULE_INFORMATION_END
	DECLARE_MODULE_INFORMATION_GETTER(AppRunner)

	AppRunner::AppRunner()
	{
	}

	AppRunner::~AppRunner()
	{
	}

	bool AppRunner::start()
	{
		return true;
	}

	bool AppRunner::stop()
	{
		return true;
	}

	bool AppRunner::update()
	{
		return true;
	}
}

using namespace apprunner;
DEFINE_MODULE_CREATION(AppRunner);
