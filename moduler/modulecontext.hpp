#ifndef MODULER_MODULECONTEXT_HPP
#define MODULER_MODULECONTEXT_HPP

#include "include/imodulecontext.hpp"
#include <map>

namespace moduler
{
	class ModuleContext : public virtual IModuleContext
	{
	public:
		ModuleContext(Moduler *const moduler) : m_moduler{ moduler } {}
		virtual ~ModuleContext() {}

		virtual IModule *requireModule(const char *moduleName) override;

	private:
		Moduler *const m_moduler;
		std::map<std::string, std::string> m_modulesConnections;
	};
}

#endif
