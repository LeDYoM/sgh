#ifndef MODULER_IMODULECONTEXT_INTERFACE_INCLUDE_HPP
#define MODULER_IMODULECONTEXT_INTERFACE_INCLUDE_HPP

#include "imodule.hpp"

namespace moduler
{
	class IModuleContext
	{
	public:
		IModuleContext() {}
		virtual ~IModuleContext() {}

		virtual IModule *requireModule(const char *moduleName) = 0;
	};
}

#endif
