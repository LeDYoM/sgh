#ifndef APPRUNNER_INTERFACE_INCLUDE_HPP
#define APPRUNNER_INTERFACE_INCLUDE_HPP

#include <loader/include/imodule.hpp>

namespace apprunner
{
	class IAppRunner : public loader::IModule
	{
	public:
		IAppRunner() {}
		virtual ~IAppRunner() {}
	};
}

DECLARE_MODULE_CREATION()

#endif
