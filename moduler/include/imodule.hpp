#ifndef MODULER_IMODULE_INTERFACE_INCLUDE_HPP
#define MODULER_IMODULE_INTERFACE_INCLUDE_HPP

#include "ibasicinterface.hpp"

namespace moduler
{
	struct ModuleInformation
	{
		const char *name;
		const char version[4];
		const char subVersion[4];
		const char patch[5];
	};
	class IModule : public virtual IBasicInterface
	{
	public:
		IModule() {}
		virtual ~IModule() {}

		virtual ModuleInformation *const moduleInformation() const = 0;
	};
}

#endif
