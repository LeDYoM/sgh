#ifndef MODULER_INCLUDE_HPP
#define MODULER_INCLUDE_HPP

#include "modulerexport.hpp"

namespace moduler
{
	class ModulerPrivate;
	class Moduler
	{
	public:
		Moduler();
		virtual ~Moduler();

		MODULER_API virtual void *loadModule(const char *fileName);
		MODULER_API virtual void *loadMethod(const char *fileName,const char *methodName);

	private:
		ModulerPrivate *m_private;
	};

	MODULER_API Moduler *createModuler();
	MODULER_API void destroyModuler();

}


#endif
