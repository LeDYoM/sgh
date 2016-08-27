#ifndef MODULER_INCLUDE_HPP
#define MODULER_INCLUDE_HPP

#include "modulerexport.hpp"
#include "imodule.hpp"

namespace moduler
{
	class ModulerPrivate;
	class Moduler
	{
	public:
		Moduler();
		~Moduler();

		MODULER_API IModule *loadModule(const char *fileName);
		MODULER_API bool unloadModule(const char *fileName);

	private:
		ModulerPrivate *m_private;
	};

	MODULER_API Moduler *createModuler();
	MODULER_API void destroyModuler();

}


#endif
