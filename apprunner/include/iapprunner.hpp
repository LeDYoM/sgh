#ifndef APPRUNNER_INTERFACE_INCLUDE_HPP
#define APPRUNNER_INTERFACE_INCLUDE_HPP

#include <moduler/include/imoduleexport.hpp>

namespace apprunner
{
	class IAppRunner : public virtual moduler::IModule
	{
	public:
		IAppRunner() {}
		virtual ~IAppRunner() {}

		virtual bool update() = 0;
	};
}

DECLARE_MODULE_CREATION

#endif
