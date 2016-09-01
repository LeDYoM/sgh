#include "include/apprunner.hpp"

namespace apprunner
{
	DECLARE_MODULE_INFORMATION_BEGIN
	DECLARE_MODULE_INFORMATION_NAME(AppRunner),
	DECLARE_MODULE_INFORMATION_VERSION(0),
	DECLARE_MODULE_INFORMATION_SUBVERSION(1),
	DECLARE_MODULE_INFORMATION_PATCH(3)
	DECLARE_MODULE_INFORMATION_END

	AppRunner::AppRunner()
	{
	}

	AppRunner::~AppRunner()
	{
	}
	moduler::ModuleInformation * const AppRunner::moduleInformation() const
	{
		return &moduleInfo;
	}

	bool AppRunner::start()
	{
		return true;
	}

	bool AppRunner::stop()
	{
		return true;
	}
}

using namespace apprunner;
DEFINE_MODULE_CREATION(AppRunner);
