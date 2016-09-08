#ifndef MODULER_MODULECONNECTION_HPP
#define MODULER_MODULECONNECTION_HPP

#include <list>

namespace moduler
{
	struct ModuleHandle;
	class ModulerPrivate;

	class ModuleConnection
	{
	public:
		explicit ModuleConnection(ModulerPrivate *modulerPrivate, ModuleHandle *source) noexcept 
			: m_modulerPrivate{ modulerPrivate }, m_source { source	} {}
		~ModuleConnection();

		bool hasModule(const ModuleHandle *const requiredModule) const noexcept;
		bool addRequiredModule(ModuleHandle *requiredModule);

	private:
		ModulerPrivate *m_modulerPrivate;
		ModuleHandle *m_source;
		std::list<ModuleHandle *> m_dest;
	};
}

#endif
