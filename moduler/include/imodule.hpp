#ifndef MODULER_IMODULE_INTERFACE_INCLUDE_HPP
#define MODULER_IMODULE_INTERFACE_INCLUDE_HPP

#include "ibasicinterface.hpp"

namespace moduler
{
	struct ModuleInformation
	{
		const char *name;
		const char *version;
		const char *subVersion;
		const char *patch;
	};
	class IModule : public virtual IBasicInterface
	{
	public:
		IModule() {}
		virtual ~IModule() {}

		virtual ModuleInformation *const moduleInformation() const = 0;
		virtual bool start() = 0;
		virtual bool stop() = 0;
	};
}

#endif
