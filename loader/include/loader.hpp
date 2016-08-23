#ifndef LOADER_INCLUDE_HPP
#define LOADER_INCLUDE_HPP

#include "loaderexport.hpp"

namespace loader
{
	class LoaderPrivate;
	class Loader
	{
	public:
		Loader();
		virtual ~Loader();

		LOADER_API virtual void *loadModule(const char *fileName);
		LOADER_API virtual void *loadMethod(const char *fileName,const char *methodName);

	private:
		LoaderPrivate *m_private;
	};

	LOADER_API Loader *createLoader();
	LOADER_API void destroyLoader();
}

#endif
