#ifndef APPRUNNER_INTERFACE_INCLUDE_HPP
#define APPRUNNER_INTERFACE_INCLUDE_HPP

#include <moduler/include/imodule.hpp>

namespace apprunner
{
	class IAppRunner : public moduler::IModule
	{
	public:
		IAppRunner() {}
		virtual ~IAppRunner() {}
	};
}

DECLARE_MODULE_CREATION()

#endif
