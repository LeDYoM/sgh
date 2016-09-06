#ifndef MODULER_MODULECONTEXT_HPP
#define MODULER_MODULECONTEXT_HPP

#include "include/imodulecontext.hpp"

namespace moduler
{
	class ModuleContext : public virtual IModuleContext
	{
	public:
		ModuleContext() {}
		virtual ~ModuleContext() {}

		virtual IModule *requireModule(const char *moduleName) override;

	};
}

#endif
