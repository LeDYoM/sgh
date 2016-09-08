#ifndef MODULER_MODULECONNECTION_HPP
#define MODULER_MODULECONNECTION_HPP

#include <list>

namespace moduler
{
	struct ModuleHandle;

	class ModuleConnection
	{
	public:
		explicit ModuleConnection(ModuleHandle *source) noexcept : m_source{ source } {}
		~ModuleConnection();

		bool hasModule(const ModuleHandle *const requiredModule) const;
		bool addRequiredModule(ModuleHandle *requiredModule);

	private:
		ModuleHandle *m_source;
		std::list<ModuleHandle *> m_dest;
	};
}

#endif
