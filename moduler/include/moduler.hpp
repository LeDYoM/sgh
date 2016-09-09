#ifndef MODULER_INCLUDE_HPP
#define MODULER_INCLUDE_HPP

#include "modulerexport.hpp"
#include "imodule.hpp"

namespace moduler
{
	class ModulerPrivate;
	struct ModuleHandle;
	using ModuleHandlePtr = ModuleHandle *;
	class Moduler
	{
	public:
		Moduler();
		~Moduler();

		MODULER_API ModuleHandlePtr loadModule(const char *fileName);
		MODULER_API bool unloadModule(ModuleHandlePtr&&);
		MODULER_API ModuleHandlePtr addDirectModule(IModule *);

	private:
		ModulerPrivate *m_private;
	};

	MODULER_API Moduler *createModuler();
	MODULER_API void destroyModuler();

}


#endif
