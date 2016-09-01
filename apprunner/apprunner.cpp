#include "include/apprunner.hpp"

#define DECLARE_MODULE_INFORMATION_BEGIN			static moduler::ModuleInformation moduleInfo =	{
#define DECLARE_MODULE_INFORMATION_NAME(name)			#name
#define DECLARE_MODULE_INFORMATION_VERSION(v)			#v
#define DECLARE_MODULE_INFORMATION_SUBVERSION(v)		#v
#define DECLARE_MODULE_INFORMATION_PATCH(v)				#v
#define DECLARE_MODULE_INFORMATION_END				};

namespace apprunner
{
	DECLARE_MODULE_INFORMATION_BEGIN
	DECLARE_MODULE_INFORMATION_NAME(AppRunner)
	DECLARE_MODULE_INFORMATION_VERSION(0)
	DECLARE_MODULE_INFORMATION_SUBVERSION(1)
	DECLARE_MODULE_INFORMATION_PATCH(2)
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
	}

	bool AppRunner::stop()
	{
	}
}

using namespace apprunner;
DEFINE_MODULE_CREATION(AppRunner);
