#include "include/apprunner.hpp"

namespace apprunner
{
	static moduler::ModuleInformation moduleInfo = 
	{
		"AppRunner",
		"0",
		"1",
		"1",
	};

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
}

using namespace apprunner;
DEFINE_MODULE_CREATION(AppRunner);
